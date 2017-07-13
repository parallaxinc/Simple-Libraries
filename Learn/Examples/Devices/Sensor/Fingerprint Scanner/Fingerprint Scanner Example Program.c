/**
 * @file Fingerprint Example Example Program.c
 *
 * @author Matthew Matz
 *
 * @version 0.50
 *
 * @copyright
 * Copyright (C) Parallax, Inc. 2017. All Rights MIT Licensed.
 *
 * @brief Demonstrates how to use each of the most common fingerprint scanner functions.
 */

#include "simpletools.h"
#include "fingerprint.h"

#define RX_PIN   8     // connect to module's TXD pin
#define TX_PIN   9     // connect to module's RXD pin


fpScanner * fpScan;

int fingerScanner(int u)
{
    int r;
    fingerprint_scan(fpScan, u, & r);
    if (u != 0 && r != 0) return 1;
    else return r;
}

int checkFingerprint;

int main()
{

    fpScan = fingerprint_open(RX_PIN, TX_PIN);

    print("Deleting all users…\r");
    fingerprint_deleteUser(fpScan, 0);

    pause(3000);
    print("Adding a new fingerprint capture to ID 5\r");
    fingerprint_add(fpScan, 5, 3, 0);

    pause(3000);
    print("Scanning and comparing to the capture for ID 5\r");
    checkFingerprint = fingerScanner(5);

    if (checkFingerprint) print("There is a match to ID 5\r");
    else  print("No matching fingerprints found!\r");

    pause(3000);
    print("Scanning and finding an ID (if any)\r");

    checkFingerprint = fingerScanner(0);
    if (checkFingerprint) print("Found a match to ID %d\r", checkFingerprint);
    else print("No matching fingerprints found!\r");

    pause(3000);
    checkFingerprint = fingerprint_countUsers(fpScan);
    print("The number of saved captures is: %d\r", checkFingerprint);

    pause(3000);
    print("Deleting the capture and information for User ID 5\r");
    fingerprint_deleteUser(fpScan, 5);
    
}




/**
 * TERMS OF USE: MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
