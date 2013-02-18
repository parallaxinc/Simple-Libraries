#include "simpletools.h"
#include "wavplayer.h"

volatile int sampleRate;
volatile int swap = 0;
volatile int playing = 0;
volatile short int wavVal;  
volatile int dacVal;
volatile unsigned int dtSample;
volatile unsigned int t;
volatile int significantBitsPerSample=16;
volatile unsigned int reps;
volatile unsigned int cog, cog2;

volatile unsigned int volume = 10;
volatile const unsigned int BUF_SIZE = 512;

unsigned int stack[(160 + (50 * 4)) / 4];
unsigned int stack2[(160 + (200 * 4)) / 4];

void play(void);
void wav_reader(void* par);

char bufferL[512];
char bufferH[512];

volatile const char* track;

FILE* fp;

//void wav_start(void)
void wav_play(const char* wavFilename)
{
  track = wavFilename;
  cog2 = cogstart(&wav_reader, NULL, stack2, sizeof(stack2));
  //while(1);
}

void wav_volume(int vol)
{
  if(vol > 10) vol = 10;
  if(vol < 0) vol = 0;
  vol = 1 << (21 - significantBitsPerSample + vol);
  unsigned int vi = volume;
  unsigned int vf = vol;   
  for(int v = vi; volume != vf;)
  { 
    if(vf > volume) volume++;
    if(vf < volume) volume--;
    if(volume == vf) break;  
  } 
}

void wav_stop(void)
{
  playing = 0;
}

void wav_reader(void* par)
{
  waitcnt(CLKFREQ+CNT);
   
  char b[4];
  int v;
  unsigned short int w;
  
  const char* trackp = (const char*) track;
  
  FILE *fp = fopen(trackp, "r");
  if(fp)
  {
    fread(b, 1, 4, fp);
    //printf("Chunk ID: %s\n", b);
    
    fread(b, 1, 4, fp);
    int fileSize = b[3] << 24 | b[2] << 16 | b[1] << 8 | b[0];
    //printf("File Size: %d\n", fileSize);
    
    fread(b, 1, 4, fp);
    //printf("RIFF Type: %s\n", b);

    fread(b, 1, 4, fp);
    //printf("Chunk ID: %s\n", b);
    
    fread(b, 1, 4, fp);
    int chunkDataSize = b[3] << 24 | b[2] << 16 | b[1] << 8 | b[0];
    //printf("Chunk data size: %d\n", chunkDataSize);

    fread(b, 1, 2, fp);
    int compressionCode = b[1] << 8 | b[0];
    //printf("Compression code: %d\n", compressionCode);

    fread(b, 1, 2, fp);
    int numberOfChannels = b[1] << 8 | b[0];
    //printf("Number of channels: %d\n", numberOfChannels);

    fread(b, 1, 4, fp);
    sampleRate = b[3] << 24 | b[2] << 16 | b[1] << 8 | b[0];
    //printf("Sample rate: %d\n", sampleRate);

    fread(b, 1, 4, fp);
    int averageBytesPerSecond = b[3] << 24 | b[2] << 16 | b[1] << 8 | b[0];
    //printf("Average bytes per second: %d\n", averageBytesPerSecond);

    fread(b, 1, 2, fp);
    int blockAlign = b[1] << 8 | b[0];
    //printf("Block align: %d\n", blockAlign);

    fread(b, 1, 2, fp);
    significantBitsPerSample = b[1] << 8 | b[0];
    //printf("Significant bits/sample: %d\n", significantBitsPerSample);

    int extraFormatBytes;
    if(compressionCode != 1)
    {
      fread(b, 1, 2, fp);
      extraFormatBytes = b[1] << 8 | b[0];
    }
    else
    {
      extraFormatBytes = 0;
    }  
    //printf("Extra format bytes: %d\n", extraFormatBytes);
    
    fread(b, 1, 4, fp);
    //printf("Chunk identifier: %s\n", b);

    fread(b, 1, 4, fp);
    int dwordChunkSize = b[3] << 24 | b[2] << 16 | b[1] << 8 | b[0];
    //printf("dword Chunk Size: %d\n", dwordChunkSize);

    unsigned int ti, tf, t, byteRate;
    ti = CNT;
    fread(bufferL, 1, 512, fp);
    tf = CNT;
    t = tf - ti;
    //printf("\nClock ticks for 512 bytes = %d\n", t); 
    byteRate = CLKFREQ*32/t*16;
    //printf("Bandwidth (bytes/sec): = %d\n\n", byteRate); 
    fread(bufferH, 1, 512, fp);
       
    cog = cogstart(&blink, NULL, stack, sizeof(stack));
    
    int reps = fileSize/1024;
    playing = 1;
    int i;
    
    for(i = 1; i < reps; i++)
    { 
      while(swap != 2);
      fread(bufferL, 1, BUF_SIZE, fp);
      while(swap != 1);
      fread(bufferH, 1, BUF_SIZE, fp);
    }
    playing = 0;
    volume = 0;
    fclose(fp);
    cogstop(cog2);
  }
  else
  {
    //printf("Couldn't read the file.");
  }
}

//__attribute__((fcache))
void blink(void *par)
{
  while(!playing);
  waitcnt(CLKFREQ/100+CNT);
  
  CTRA = 0x18000000 + 27;
  CTRB = 0x18000000 + 26;

  DIRA |= (1<<27);
  DIRA |= (1<<26);
  dtSample = CLKFREQ/sampleRate;
  play();  
}  

//__attribute__((fcache))
void play(void)
{
  t = CNT;
  t+=dtSample;
  int i;
  while(playing)
  {
    swap = 1;
    for(i = 0; i < BUF_SIZE; i+=2)
    {
      wavVal = bufferL[i] | bufferL[i+1]<<8;
      dacVal = (wavVal + 32768) * volume;
      FRQA = dacVal;
      FRQB = dacVal;
      waitcnt(t+=dtSample);
    }
    swap = 2;
    for(i = 0; i < BUF_SIZE; i+=2)
    {
      wavVal = bufferH[i] | bufferH[i+1]<<8;
      dacVal = (wavVal + 32768) * volume;
      FRQA = dacVal;
      FRQB = dacVal;
      waitcnt(t+=dtSample);
    }
  }
  cogstop(cog);
}
    





