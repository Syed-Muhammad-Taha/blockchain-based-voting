#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include "sha256.c"
#include "sha256.h"
#define maxLength 256
#define cnicLength 20

void green(){
    printf("\033[0;32m");
}

void black(){
    printf("\033[0;30m");
}

void red() {
    printf("\033[1;31m");
}

void yellow() {
    printf("\033[1;33m");
}

void cyan() {
    printf("\033[0;36m");
}

void blue(){
    printf("\033[0;34m");
}

void purple(){
    printf("\033[0;35m");
}

void reset() {
    printf("\033[0m");
}


/**
 * A simple struct to represent a voter.
 *
 * @param blockNumber The block number of the voter.
 * @param name The name of the voter.
 * @param cnic The CNIC of the voter.
 * @param domicile The domicile of the voter.
 * @param voteTo The vote to be casted.
 * @param nameHash The hash of the name of the voter.
 * @param voteStatus The status of the vote.
 */
struct Voter {
    char time[50];
    char voterPrivkey[66];
    char name[30];
    char cnic[cnicLength];
    char domicile[30];
    int voteTo;
    char voteStatus;
    char isValidated;
};



/**
 * A struct to represent a block in the blockchain.
 *
 * @param minedStatus The status of the block.
 * @param nextBlock The next block in the blockchain.
 * @param prevBlock The previous block in the blockchain.
 * @param voterDetails The details of the voters who voted for this block.
 * @param blockNumber The number of the block.
 * @param prevHash The previous hash of the block.
 * @param currentHash The current hash of the block.
 * @param nonce The nonce of the block.
 * @param timestamp The timestamp of the block.
 */
struct Block{
    char minedStatus;
    struct Block* nextBlock;
    struct Block* prevBlock;
    struct Voter voterDetails[3];
    int blockNumber;
    char prevHash[66];
    char currentHash[66];
    int nonce;
    char timestamp[50];
};

struct Block* Genesis;
struct Block* newBlock;
char name[30] = {0};
int voteTo;
int voteSign = 0;
char cnic[cnicLength] = {0};
char domicile[30] = {0};
char password[30] = {0};
int voteNum = 0;
int blockNumber;
struct Block* tempBlock;
struct Block* tempCheckBlock;
struct Block* minerBlock;
char* concatText;
char* memoryHash;
char* tempConcat;

/**
 * Initializes a new block.
 *
 * @param newBlock The new block to initialize.
 *
 * @returns None
 */
void initBlockN(struct Block* newBlock) {
    tempBlock->nextBlock = newBlock;
    tempBlock->nextBlock->prevBlock = tempBlock;
    tempBlock = tempBlock->nextBlock;
}

/**
 * Generates a timestamp.
 *
 * @returns A string containing the current time.
 */
const char* generateTimeStamp() {
    time_t* timestamp;
    time(timestamp);
    return ctime(timestamp);
}



/**
 * Generates a SHA-256 hash for a given string.
 *
 * @param word The string to hash.
 *
 * @returns The SHA-256 hash of the string.
 */
char* generateHash(char* word) {
    memoryHash = realloc(memoryHash, 66);
    uint8_t hash[32];
    char* hashString;
    hashString = memoryHash;
    calc_sha_256(hash, word, strlen(word));
    hash_to_string(hashString, hash);
    return hashString;
}




/**
 * Concatenates the voter details of the block.
 *
 * @returns The concatenated voter details of the block.
 */
char* voterDetailsConcat(){
    concatText = realloc(concatText,maxLength);
    sprintf(concatText, "%s%s%s%s%s%s%s%s%s%s", tempBlock->voterDetails[0].name, tempBlock->voterDetails[0].cnic, tempBlock->voterDetails[0].domicile, tempBlock->voterDetails[1].name, tempBlock->voterDetails[1].cnic, tempBlock->voterDetails[1].domicile, tempBlock->voterDetails[2].name, tempBlock->voterDetails[2].cnic, tempBlock->voterDetails[2].domicile,tempBlock->prevHash);
    return concatText;
}

char* forMiner(struct Block *block) {
    concatText = realloc(concatText, maxLength);
    sprintf(concatText, "%s%s%s%s%s%s%s%s%s%s", block->voterDetails[0].name, block->voterDetails[0].cnic, block->voterDetails[0].domicile, block->voterDetails[1].name, block->voterDetails[1].cnic, block->voterDetails[1].domicile, block->voterDetails[2].name, block->voterDetails[2].cnic, block->voterDetails[2].domicile, block->prevHash);
    return concatText;
}

/**
 * Delays the program for a specified number of milliseconds.
 *
 * @param milliseconds The number of milliseconds to delay.
 *
 * @returns None
 */
void delay(int milliseconds) {
    long pause;
    clock_t now, then;

    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();
    while ((now - then) < pause)
        now = clock();
}



/**
 * Mines a block for the blockchain.
 *
 * @param stringConcat The string to concatenate with the nonce.
 *
 * @returns None
 */
void mineBlock( char* stringConcat ){
    long long nonce = 1;

    while (1) {
        tempConcat = realloc(tempConcat, maxLength);
        strcpy(tempConcat, stringConcat);
        sprintf(tempConcat, "%s%lld", stringConcat, nonce);
        if ((generateHash(tempConcat))[0] == '0' && (generateHash(tempConcat))[1] == '0' && (generateHash(tempConcat))[2] == '0' && (generateHash(tempConcat))[3] == '0' && (generateHash(tempConcat))[4] == '0') {
            minerBlock->nonce = nonce;
            strcpy(minerBlock->currentHash, generateHash(tempConcat));
            break;
        } else {
            nonce++;
        }
    }
}

// Displays Home Prompt
void homeScreen() {
    blue();
    printf(
        ""
        "                _______   __                      __                  __                  __                  __                                            __ \n"
        "               /       \\ /  |                    /  |                /  |                /  |                /  |                                          /  |\n"
        "               $$$$$$$  |$$ |  ______    _______ $$ |   __   _______ $$ |____    ______  $$/  _______        $$ |____    ______    _______   ______    ____$$ |\n"
        "               $$ |__$$ |$$ | /      \\  /       |$$ |  /  | /       |$$      \\  /      \\ /  |/       \\       $$      \\  /      \\  /       | /      \\  /    $$ |\n"
        "               $$    $$< $$ |/$$$$$$  |/$$$$$$$/ $$ |_/$$/ /$$$$$$$/ $$$$$$$  | $$$$$$  |$$ |$$$$$$$  |      $$$$$$$  | $$$$$$  |/$$$$$$$/ /$$$$$$  |/$$$$$$$ |\n"
        "               $$$$$$$  |$$ |$$ |  $$ |$$ |      $$   $$<  $$ |      $$ |  $$ | /    $$ |$$ |$$ |  $$ |      $$ |  $$ | /    $$ |$$      \\ $$    $$ |$$ |  $$ |\n"
        "               $$ |__$$ |$$ |$$ \\__$$ |$$ \\_____ $$$$$$  \\ $$ \\_____ $$ |  $$ |/$$$$$$$ |$$ |$$ |  $$ |      $$ |__$$ |/$$$$$$$ | $$$$$$  |$$$$$$$$/ $$ \\__$$ |\n"
        "               $$    $$/ $$ |$$    $$/ $$       |$$ | $$  |$$       |$$ |  $$ |$$    $$ |$$ |$$ |  $$ |      $$    $$/ $$    $$ |/     $$/ $$       |$$    $$ |\n"
        "               $$$$$$$/  $$/  $$$$$$/   $$$$$$$/ $$/   $$/  $$$$$$$/ $$/   $$/  $$$$$$$/ $$/ $$/   $$/       $$$$$$$/   $$$$$$$/ $$$$$$$/   $$$$$$$/  $$$$$$$/ \n"
        "                                                                                                                                                                       \n"
        "                                                                                                                                                                       \n"
        "                                                                                                                                                                       \n"
        "                              __     __             __      __                             ______                                                                      \n"
        "                             /  |   /  |           /  |    /  |                           /      \\                                                                     \n"
        "                             $$ |   $$ | ______   _$$ |_   $$/  _______    ______        /$$$$$$  |  ______    ______                                                  \n"
        "                             $$ |   $$ |/      \\ / $$   |  /  |/       \\  /      \\       $$ |__$$ | /      \\  /      \\                                             \n"
        "                             $$  \\ /$$//$$$$$$  |$$$$$$/   $$ |$$$$$$$  |/$$$$$$  |      $$    $$ |/$$$$$$  |/$$$$$$  |                                                \n"
        "                              $$  /$$/ $$ |  $$ |  $$ | __ $$ |$$ |  $$ |$$ |  $$ |      $$$$$$$$ |$$ |  $$ |$$ |  $$ |                                                \n"
        "                               $$ $$/  $$ \\__$$ |  $$ |/  |$$ |$$ |  $$ |$$ \\__$$ |      $$ |  $$ |$$ |__$$ |$$ |__$$ |                                                \n"
        "                                $$$/   $$    $$/   $$  $$/ $$ |$$ |  $$ |$$    $$ |      $$ |  $$ |$$    $$/ $$    $$/                                                 \n"
        "                                 $/     $$$$$$/     $$$$/  $$/ $$/   $$/  $$$$$$$ |      $$/   $$/ $$$$$$$/  $$$$$$$/                                                  \n"
        "                                                                         /  \\__$$ |                $$ |      $$ |                                                      \n"
        "                                                                         $$    $$/                 $$ |      $$ |                                                      \n"
        "                                                                          $$$$$$/                  $$/       $$/                                                       \n"
        "                                                                                                                                                                       \n"
        "                                                                                                                                                                       \n"
        "                                                                                                                                                                       \n");
    cyan();
    printf(
        "                                                                                                                                                                       \n"
        "                   +----------------------------------------+                       +--------------------------------+                                                 \n"
        "                   |  ___  ____  ___  _  _    __  __  ____  |                       |  __    _____  ___  ____  _  _  |                                                 \n"
        "                   | / __)(_  _)/ __)( \\( )  (  )(  )(  _ \\ |                       | (  )  (  _  )/ __)(_  _)( \\( ) |                                                \n"
        "                   | \\__ \\ _)(_( (_-. )  (    )(__)(  )___/ |                       |  )(__  )(_)(( (_-. _)(_  )  (  |                                                 \n"
        "                   | (___/(____)\\___/(_)\\_)  (______)(__)   |                       | (____)(_____)\\___/(____)(_)\\_) |                                               \n"
        "                   +----------------------------------------+                       +--------------------------------+                                                 \n");

    
}

// Displays Sign Up Prompt
void signUp(){
    purple();
    printf("\n\n\n\n"
        "                 /$$$$$$  /$$\n"
        "                /$$__  $$|__/  \n"
        "               | $$  \\__/ /$$  /$$$$$$  /$$$$$$$  /$$   /$$  /$$$$$$ \n"
        "               |  $$$$$$ | $$ /$$__  $$| $$__  $$| $$  | $$ /$$__  $$\n"
        "                \\____  $$| $$| $$  \\ $$| $$  \\ $$| $$  | $$| $$  \\ $$\n"
        "                /$$  \\ $$| $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$\n"
        "               |  $$$$$$/| $$|  $$$$$$$| $$  | $$|  $$$$$$/| $$$$$$$/\n"
        "                \\______/ |__/ \\____  $$|__/  |__/ \\______/ | $$____/ \n"
        "                              /$$  \\ $$                    | $$      \n"
        "                             |  $$$$$$/                    | $$      \n"
        "                              \\______/                     |__/      \n\n\n\n\n");
}


// Displays Successfully Registered Prompt
void successfullyRegistered(){
    green();
    printf("\n\n\n\n"
        "                    /$$$$$$$                      /$$             /$$\n"
        "                   | $$__  $$                    |__/            | $$\n"
        "                   | $$  \\ $$  /$$$$$$   /$$$$$$  /$$  /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$         /$$$$$$$ /$$   /$$  /$$$$$$$  /$$$$$$$  /$$$$$$   /$$$$$$$ /$$$$$$$\n"
        "                   | $$$$$$$/ /$$__  $$ /$$__  $$| $$ /$$_____/|_  $$_/   /$$__  $$ /$$__  $$       /$$_____/| $$  | $$ /$$_____/ /$$_____/ /$$__  $$ /$$_____//$$_____/\n"
        "                   | $$__  $$| $$$$$$$$| $$  \\ $$| $$|  $$$$$$   | $$    | $$$$$$$$| $$  \\__/      |  $$$$$$ | $$  | $$| $$      | $$      | $$$$$$$$|  $$$$$$|  $$$$$$\n"
        "                   | $$  \\ $$| $$_____/| $$  | $$| $$ \\____  $$  | $$ /$$| $$_____/| $$             \\____  $$| $$  | $$| $$      | $$      | $$_____/ \\____  $$\\____  $$\n"
        "                   | $$  | $$|  $$$$$$$|  $$$$$$$| $$ /$$$$$$$/  |  $$$$/|  $$$$$$$| $$             /$$$$$$$/|  $$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$ /$$$$$$$//$$$$$$$/\n"
        "                   |__/  |__/ \\_______/ \\____  $$|__/|_______/    \\___/   \\_______/|__/            |_______/  \\______/  \\_______/ \\_______/ \\_______/|_______/|_______/\n"
        "                                        /$$  \\ $$        \n"
        "                                       |  $$$$$$/          \n"
        "                                        \\______/          \n\n\n\n\n"

    );
}


// Displays Login Prompt
void login(){
    cyan();
    printf("\n\n\n\n"
        "                    /$$                           /$$          \n"
        "                   | $$                          |__/          \n"
        "                   | $$        /$$$$$$   /$$$$$$  /$$ /$$$$$$$ \n"
        "                   | $$       /$$__  $$ /$$__  $$| $$| $$__  $$\n"
        "                   | $$      | $$  \\ $$| $$  \\ $$| $$| $$  \\ $$\n"
        "                   | $$      | $$  | $$| $$  | $$| $$| $$  | $$\n"
        "                   | $$$$$$$$|  $$$$$$/|  $$$$$$$| $$| $$  | $$\n"
        "                   |________/ \\______/  \\____  $$|__/|__/  |__/\n"
        "                                        /$$  \\ $$              \n"
        "                                       |  $$$$$$/              \n"
        "                                        \\______/               \n\n\n\n\n");
}


// Displays Record Present Prompt
void recordPresent(){
    printf("\n\n\n\n\n"
        "        /$$$$$$$                                                /$$                                                                     /$$\n"
        "       | $$__  $$                                              | $$                                                                    | $$\n"
        "       | $$  \\ $$  /$$$$$$   /$$$$$$$  /$$$$$$   /$$$$$$   /$$$$$$$        /$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$$  /$$$$$$  /$$$$$$$  /$$$$$$\n"
        "       | $$$$$$$/ /$$__  $$ /$$_____/ /$$__  $$ /$$__  $$ /$$__  $$       /$$__  $$ /$$__  $$ /$$__  $$ /$$_____/ /$$__  $$| $$__  $$|_  $$_/\n"
        "       | $$__  $$| $$$$$$$$| $$      | $$  \\ $$| $$  \\__/| $$  | $$      | $$  \\ $$| $$  \\__/| $$$$$$$$|  $$$$$$ | $$$$$$$$| $$  \\ $$  | $$\n"
        "       | $$  \\ $$| $$_____/| $$      | $$  | $$| $$      | $$  | $$      | $$  | $$| $$      | $$_____/ \\____  $$| $$_____/| $$  | $$  | $$ /$$\n"
        "       | $$  | $$|  $$$$$$$|  $$$$$$$|  $$$$$$/| $$      |  $$$$$$$      | $$$$$$$/| $$      |  $$$$$$$ /$$$$$$$/|  $$$$$$$| $$  | $$  |  $$$$/\n"
        "       |__/  |__/ \\_______/ \\_______/ \\______/ |__/       \\_______/      | $$____/ |__/       \\_______/|_______/  \\_______/|__/  |__/   \\___/\n"
        "                                                                         | $$                                                                  \n"
        "                                                                         | $$                                                                  \n"
        "        /$$$$$$$$                        /$$                             |_/$$                           /$$                                   \n"
        "       |__  $$__/                       | $$                              |__/                          |__/                                   \n"
        "          | $$  /$$$$$$  /$$   /$$      | $$  /$$$$$$   /$$$$$$   /$$$$$$  /$$ /$$$$$$$   /$$$$$$        /$$ /$$$$$$$                          \n"
        "          | $$ /$$__  $$| $$  | $$      | $$ /$$__  $$ /$$__  $$ /$$__  $$| $$| $$__  $$ /$$__  $$      | $$| $$__  $$                         \n"
        "          | $$| $$  \\__/| $$  | $$      | $$| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$| $$  \\ $$| $$  \\ $$      | $$| $$  \\ $$                  \n"
        "          | $$| $$      | $$  | $$      | $$| $$  | $$| $$  | $$| $$  | $$| $$| $$  | $$| $$  | $$      | $$| $$  | $$                         \n"
        "          | $$| $$      |  $$$$$$$      | $$|  $$$$$$/|  $$$$$$$|  $$$$$$$| $$| $$  | $$|  $$$$$$$      | $$| $$  | $$                         \n"
        "          |__/|__/       \\____  $$      |__/ \\______/  \\____  $$ \\____  $$|__/|__/  |__/ \\____  $$      |__/|__/  |__/                    \n"
        "                         /$$  | $$                     /$$  \\ $$ /$$  \\ $$               /$$  \\ $$                                          \n"
        "                        |  $$$$$$/                    |  $$$$$$/|  $$$$$$/              |  $$$$$$/                                             \n"
        "                         \\______/                      \\______/  \\______/                \\______/                                          \n\n\n\n\n\n\n");
}



void noRecord(){
    red();
    printf("\n\n\n\n\n"
        " /$$   /$$                 /$$$$$$$                                                /$$       /$$$$$$$$                                  /$$\n"
        "| $$$ | $$                | $$__  $$                                              | $$      | $$_____/                                 | $$\n"
        "| $$$$| $$  /$$$$$$       | $$  \\ $$  /$$$$$$   /$$$$$$$  /$$$$$$   /$$$$$$   /$$$$$$$      | $$     /$$$$$$  /$$   /$$ /$$$$$$$   /$$$$$$$\n"
        "| $$ $$ $$ /$$__  $$      | $$$$$$$/ /$$__  $$ /$$_____/ /$$__  $$ /$$__  $$ /$$__  $$      | $$$$$ /$$__  $$| $$  | $$| $$__  $$ /$$__  $$\n"
        "| $$  $$$$| $$  \\ $$      | $$__  $$| $$$$$$$$| $$      | $$  \\ $$| $$  \\__/| $$  | $$      | $$__/| $$  \\ $$| $$  | $$| $$  \\ $$| $$  | $$\n"
        "| $$\\  $$$| $$  | $$      | $$  \\ $$| $$_____/| $$      | $$  | $$| $$      | $$  | $$      | $$   | $$  | $$| $$  | $$| $$  | $$| $$  | $$\n"
        "| $$ \\  $$|  $$$$$$/      | $$  | $$|  $$$$$$$|  $$$$$$$|  $$$$$$/| $$      |  $$$$$$$      | $$   |  $$$$$$/|  $$$$$$/| $$  | $$|  $$$$$$$\n"
        "|__/  \\__/ \\______/       |__/  |__/ \\_______/ \\_______/ \\______/ |__/       \\_______/      |__/    \\______/  \\______/ |__/  |__/ \\_______/\n"
        "\n\n\n\n");
}


void voterPage(){
    printf("\n\n\n\n");
    yellow();
    printf(
        "   +------------------------------------------------------------------+\n"
        "   |     ___  _   _  ____  ___  _  _    _  _  _____  ____  ____       |\n"
        "   |    / __)( )_( )( ___)/ __)( )/ )  ( \\/ )(  _  )(_  _)( ___)      |\n"
        "   |   ( (__  ) _ (  )__)( (__  )  (    \\  /  )(_)(   )(   )__)       |\n"
        "   |    \\___)(_) (_)(____)\\___)(_)\\_)    \\/  (_____) (__) (____)      |\n"
        "   +------------------------------------------------------------------+\n\n\n\n");

    green();
    printf(
        "   +------------------------------------------------------+\n"
        "   |  ___    __    ___  ____    _  _  _____  ____  ____   | \n"
        "   | / __)  /__\\  / __)(_  _)  ( \\/ )(  _  )(_  _)( ___)  | \n"
        "   |( (__  /(__)\\ \\__ \\  )(     \\  /  )(_)(   )(   )__    |\n"
        "   | \\___)(__)(__)(___/ (__)     \\/  (_____) (__) (____)  |   \n"
        "   +------------------------------------------------------+\n\n\n\n");
    red();
    printf(
        "   +---------------------------------------+\n"
        "   | __    _____  ___  _____  __  __  ____ |\n"
        "   |(  )  (  _  )/ __)(  _  )(  )(  )(_  _)|\n"
        "   | )(__  )(_)(( (_-. )(_)(  )(__)(   )(  |\n"
        "   |(____)(_____)\\___/(_____)(______) (__) |\n"
        "   +---------------------------------------+\n\n\n");
}


void welcomeVoter(){
    purple();
    printf("\n\n\n\n\n"
        "       $$\\      $$\\           $$\\                                                   $$\\    $$\\            $$\\                         \n"
        "       $$ | $\\  $$ |          $$ |                                                  $$ |   $$ |           $$ |                        \n"
        "       $$ |$$$\\ $$ | $$$$$$\\  $$ | $$$$$$$\\  $$$$$$\\  $$$$$$\\$$$$\\   $$$$$$\\        $$ |   $$ | $$$$$$\\ $$$$$$\\    $$$$$$\\   $$$$$$\\  \n"
        "       $$ $$ $$\\$$ |$$  __$$\\ $$ |$$  _____|$$  __$$\\ $$  _$$  _$$\\ $$  __$$\\       \\$$\\  $$  |$$  __$$\\\\_$$  _|  $$  __$$\\ $$  __$$\\ \n"
        "       $$$$  _$$$$ |$$$$$$$$ |$$ |$$ /      $$ /  $$ |$$ / $$ / $$ |$$$$$$$$ |       \\$$\\$$  / $$ /  $$ | $$ |    $$$$$$$$ |$$ |  \\__|\n"
        "       $$$  / \\$$$ |$$   ____|$$ |$$ |      $$ |  $$ |$$ | $$ | $$ |$$   ____|        \\$$$  /  $$ |  $$ | $$ |$$\\ $$   ____|$$ |      \n"
        "       $$  /   \\$$ |\\$$$$$$$\\ $$ |\\$$$$$$$\\ \\$$$$$$  |$$ | $$ | $$ |\\$$$$$$$\\          \\$  /   \\$$$$$$  | \\$$$$  |\\$$$$$$$\\ $$ |      \n"
        "       \\__/     \\__| \\_______|\\__| \\_______| \\______/ \\__| \\__| \\__| \\_______|          \\_/     \\______/   \\____/  \\_______|\\__|      \n");
}


void alreadyVoted(){
    red();
    printf("\n\n\n\n"
        ""
        "       $$$$$$\\                                                      $$$\\                                                       \n"
        "       $$  __$$\\                                                    $$  _|                                                     \n"
        "       $$ /  \\__| $$$$$$\\   $$$$$$\\   $$$$$$\\  $$\\   $$\\       $$\\ $$  /                                                       \n"
        "       \\$$$$$$\\  $$  __$$\\ $$  __$$\\ $$  __$$\\ $$ |  $$ |      \\__|$$ |                                                        \n"
        "        \\____$$\\ $$ /  $$ |$$ |  \\__|$$ |  \\__|$$ |  $$ |          $$ |                                                        \n"
        "       $$\\   $$ |$$ |  $$ |$$ |      $$ |      $$ |  $$ |      $$\\ \\$$\\                                                        \n"
        "       \\$$$$$$  |\\$$$$$$  |$$ |      $$ |      \\$$$$$$$ |      \\__| \\$$$\\                                                      \n"
        "        \\______/  \\______/ \\__|      \\__|       \\____$$ |            \\___|                                                     \n"
        "        $$$$$$\\  $$\\                           $$\\   $$ |$$\\                 $$\\    $$\\            $$\\                     $$\\ \n"
        "       $$  __$$\\ $$ |                          \\$$$$$$  |$$ |                $$ |   $$ |           $$ |                    $$ |\n"
        "       $$ /  $$ |$$ | $$$$$$\\   $$$$$$\\   $$$$$$\\___$$$$$$$ |$$\\   $$\\       $$ |   $$ | $$$$$$\\ $$$$$$\\    $$$$$$\\   $$$$$$$ |\n"
        "       $$$$$$$$ |$$ |$$  __$$\\ $$  __$$\\  \\____$$\\ $$  __$$ |$$ |  $$ |      \\$$\\  $$  |$$  __$$\\\\_$$  _|  $$  __$$\\ $$  __$$ |\n"
        "       $$  __$$ |$$ |$$ |  \\__|$$$$$$$$ | $$$$$$$ |$$ /  $$ |$$ |  $$ |       \\$$\\$$  / $$ /  $$ | $$ |    $$$$$$$$ |$$ /  $$ |\n"
        "       $$ |  $$ |$$ |$$ |      $$   ____|$$  __$$ |$$ |  $$ |$$ |  $$ |        \\$$$  /  $$ |  $$ | $$ |$$\\ $$   ____|$$ |  $$ |\n"
        "       $$ |  $$ |$$ |$$ |      \\$$$$$$$\\ \\$$$$$$$ |\\$$$$$$$ |\\$$$$$$$ |         \\$  /   \\$$$$$$  | \\$$$$  |\\$$$$$$$\\ \\$$$$$$$ |\n"
        "       \\__|  \\__|\\__|\\__|       \\_______| \\_______| \\_______| \\____$$ |          \\_/     \\______/   \\____/  \\_______| \\_______|\n"
        "                                                             $$\\   $$ |                                                        \n"
        "                                                             \\$$$$$$  |                                                        \n"
        "                                                              \\______/                                                         \n"

        "\n\n\n\n");
}

void voteRegistered(){
    green();
    printf("\n\n\n\n\n"
        ""
        "       $$\\    $$\\            $$\\                                                                                      \n"
        "       $$ |   $$ |           $$ |                                                                                     \n"
        "       $$ |   $$ | $$$$$$\\ $$$$$$\\    $$$$$$\\                                                                         \n"
        "       \\$$\\  $$  |$$  __$$\\\\_$$  _|  $$  __$$\\                                                                        \n"
        "        \\$$\\$$  / $$ /  $$ | $$ |    $$$$$$$$ |                                                                       \n"
        "         \\$$$  /  $$ |  $$ | $$ |$$\\ $$   ____|                                                                       \n"
        "          \\$  /   \\$$$$$$  | \\$$$$  |\\$$$$$$$\\                                                                        \n"
        "       $$$$$$$\\    \\______/   \\____/ $$\\______|      $$\\                                         $$\\           $$$\\   \n"
        "       $$  __$$\\                     \\__|            $$ |                                        $$ |           \\$$\\  \n"
        "       $$ |  $$ | $$$$$$\\   $$$$$$\\  $$\\  $$$$$$$\\ $$$$$$\\    $$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$$ |      $$\\   \\$$\\ \n"
        "       $$$$$$$  |$$  __$$\\ $$  __$$\\ $$ |$$  _____|\\_$$  _|  $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$ |      \\__|   $$ |\n"
        "       $$  __$$< $$$$$$$$ |$$ /  $$ |$$ |\\$$$$$$\\    $$ |    $$$$$$$$ |$$ |  \\__|$$$$$$$$ |$$ /  $$ |             $$ |\n"
        "       $$ |  $$ |$$   ____|$$ |  $$ |$$ | \\____$$\\   $$ |$$\\ $$   ____|$$ |      $$   ____|$$ |  $$ |      $$\\   $$  |\n"
        "       $$ |  $$ |\\$$$$$$$\\ \\$$$$$$$ |$$ |$$$$$$$  |  \\$$$$  |\\$$$$$$$\\ $$ |      \\$$$$$$$\\ \\$$$$$$$ |      \\__|$$$  / \n"
        "       \\__|  \\__| \\_______| \\____$$ |\\__|\\_______/    \\____/  \\_______|\\__|       \\_______| \\_______|          \\___/  \n"
        "                           $$\\   $$ |                                                                                 \n"
        "                           \\$$$$$$  |                                                                                 \n"
        "                            \\______/                                                                                  \n"
        "\n\n\n\n");
}



void mqm(){
    black();
    printf(
        "OOOOOOOOOOOOOOOO0000O00000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOd       \n"
        "OOOOOOOOOOOO0OOOOOOOO0000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO0OOOOOOOOOOOOOOOOOd       \n"
        "OOOOOOOOO000000000OOO0000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO00OOOOOOOOOOOOOOOOOOd       \n"
        "OkOOOOOOOOOOO000000000000000000000000000000OOOOOxocoxOOOOOOOOOOOOOOOOOOOOOOOOOO0OOOOOOOOOOOOOOOOOOOd       \n"
        "OOOOOOOOOOOOO0000000000000000000000000000OOOOOkl;'.';lxOOOOOOOOOOOOOOOOOOOOOOOO00000OOOOOOOOOOOOOOOd       \n"
        "OOOOOOOOOOOOOOOOOOOO0000000000000OOO00000OOOko:cooclol:cdOOOOOOOOOOOOOOOOOOOOOO0000000OOOOOOOOOOOOOd       \n"
        "OOOOOOOOOOOOOOOOOO0000OOO00000000OOOO0OOOOkocldOOo:lxOxl:cdkOOOOOOOOOOOOOOOOOOOO00OO00000OOOOOOOOOOd       \n"
        "OOOOOOOOOOOOO00000000OOOO00000OOOOOOOOOOkoccdOOOOoclxOOOxl;cokOOOOOOOOOOOOOOOOOOOOOOOO00000OOOOOOOOd       \n"
        "OOOOOOOOOOOO0000000000000000OOOOOOO0OOko:cdkOOOOOoclxOOOOkxl:cdkOOOOOOOOOOOOOOOOOOOOOOO000000OOOOOOd       \n"
        "OOOOOOOOOOOOOOOO000000000000OOOOOOO0Odc:okOOOOOOOo:cxOOkkOkkxoccokOOOOOOOOOOOOOOOOOO00OOOOOOOOOO000d       \n"
        "OOOOOOOOOOOOOOO00OOOO000000000OOOOkdlcokOOOOOOOOkl;cxOOkkkkOOOko:;lxOOOOOOOOOOOOOOOO00OOOOOOOOOO000d       \n"
        "OOOOOOOOOOOOOOOOOOOOO000000000OOko:cdkOOOOOOOOOOkl,:xOkkkkOOOOOOko:;lxOOOOOOOOOOOOOOOOOOOOOOOOOOOOOd       \n"
        "OOOOOOOOOOOO0OOOO00OO000000OO0Od::okOOOOOOOOOOOOkl,:dkkkkkkkOOOOOOko:;cxOOOOOOOOOOOOOOOOOOOOOOOOkkOd       \n"
        "OOOOO0000OOOOOOO000OO0OO0OOOOdccokOOOOOOOOOOOOOkl,.;dOkkkkkkkkkkOOOkkdc;:okOOOOOOOOOOOOOOOOOOOOOOOOd       \n"
        "OOOOO000OOOOOOOOO00OOOOOOOOdlcokOOOOOkOOOOkkkxo::,':xOkkkkkkkkkkkkkkkkkxl::okOOOOOOOOOOOOOOOOOOOOOOd       \n"
        "OOOOOOOOOOOOOOOOOOOOOOOOOdccokOOkdl:,,,:ldxdccldxl;cxOkkkkkkkkxdoodxkkkkkxl;;lxOOOOOOOOOOOOOOOO00OOd       \n"
        "OOOOOOOOOOOOOOOOO00OOOOxlcokOOko;.       ..':dkOkl:cxOOkkkkxl,.. ...;lxkkOOxl;:oxOOOOOOOOOOOOOOOOOOd       \n"
        "OOOOOOOOO00O00000O00OxlcokOOOkc.           .:xkkkl;cxOkOOxc.          ,okkOOkko::lxOOOOOOOOOOOOOOOOo       \n"
        "OOOOOOOOOOOO000OOOOxlclkOOOOOo.             .ckOkc,:xOkkkc.            'okOOOOOkdc;lxkOOOOOOOOOOOOOo       \n"
        "OOOOOOOOOOO00OO00kocoxOOOOOOOl.              ;xOxc,:xOkkd,             .ckOOOOOOOkdc;cdkOOOOOOOOOOOd       \n"
        "OOOOOOOOOOOOOOkdlcokOOOOOOOOOo.             .ckkxc':xOOOx;             .ckOOOOOkkOOOxl:cdkOOOOOOOOOd       \n"
        "OOOOOOOOOOOOOOd;;dOOOOOOOOOOOk:.           .:xOOxc,:xOkkko.            ;xOOOOOOOOOOOOOd;:xOOOOOOOOOd       \n"
        "OOOOOOOOOOOOOOkoccokOOOOOOOOxlc:'.       .'lxkOOkl;cxkkkkko,.        .cxOOOOOOOOOOOOkdclxO0000OOOOOd       \n"
        "OOOOOOOOOOOOOOOOOdc:dkOOOOxllokOkdc;,,,;cokkkkkOxl;lxkkkkkOko:,''',:lxOOOOOOOOOOOOkdlldOOOO00000OOOd       \n"
        "OOOOOOOOOOOOOOOOOOko::oxdlldkOOOOOOOOOOOOOOOOOkkxc,cxkkkkkOOOOkkkkOOOOOOOOOOOOOOkdccdOOOOOOOOO00OOOd       \n"
        "OOOOOOOOO00O0OOOOOOOx:..,okOOOOOOOOOOOOOOOOOOOkkxl;cxkkkkkOOOOOOOOOOOOOOOOOOOOOdc:okOOOOOOOO00OOOOOd       \n"
        "O0OOOOO0000000OOOxdooc:,,,:ooooddxxkkOOOOOOOOOOOkl:lkOOOOOOOOOOOOOOOOOOOOOOOOxl:lxOOOOOOOOOOOOO0000d       \n"
        "0OOO0OOOO000OkxolloxOOOOxc;:lddooolllooooddxxxxkxl:okOOkkOOOkOOOOOOOOOOOOOOkl;cxOOOOOOOOOOOOOOOO000d       \n"
        "OOOO00OOOkxdlodxkO0000OOOOxl;cxOOOOOkkxxddoooollc;,ckOOOOOOOOOOOOOOOOOOOOkl:cxOOOOOOOO0000000OOOOO0d       \n"
        "OOOOOkxdoodxkO0000000000OOOOxc:lxOOOO00OOOOOOOOkd:,cxOOOOOOOOOOOOOOOOOOko::dkOOOOOOOOO00000O0000OOOd       \n"
        "0OxdoodxxkOO0000000000000OOOOkdc:lkOOOOOOOOOOOOOxc,ckOkkkkOOOOOOOOOOOko::okOOOOOOOOOOOO000OOOO0000Od       \n"
        "ooodxkOOOOOOO000000000000OOOOOOOd::okOOOOOOOOOOOx:,cxkkkkOOOOOOOOkkko::lkOOOOOOOOOOOOOOOOOOOOO0OOO0d       \n"
        "dkOOOOOOOOOOOOOOOOOOO000OOOO0OOOOkoccokOOOOOOOOko,.;dkkkOOOOOOOOOko:;lkOOOOOOOOOOOOOOO00OOOOOOOOOO0d       \n"
        "OOOOOOOOOOOOOOOOOOOOOO000OOOOOOOOOOko::okOOOOko;.   'cxOOOOOOOOOdc;cxOOOOOOOOOOOOOOO00OOOOO000OOO00d       \n"
        "OOOOO00000OOOOOOOOOOOO00OOOOOOOOOOOOOko:cokko;.       .cdkkkOOdc;cdkOOOOkOOOOOOOOOO0000O0000000OO00d       \n"
        "OOOOOOO00OOOOOOOOOOO000OOOOOOOOOOOOOOOOko;,'.           .:xkd:,:dkkkkkkkkOOOOOOOOO0000000000000OOO0d       \n"
        "OOOOOOOOOOOOOOOOOO0000OOOOOOOOOOOOOOOOOko'                .'';okkkkOOkkkOOOOOOOOOO0000000000OOOOOO0d       \n"
        "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkl,.                    ,oxkkkOOOOOOOOOOOOOOOOOOOO0000OOOO0000d       \n"
        "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOxl'         1. MQM          'lxkkkOOOOOOOOOOOOOOOOOO000OOOOOOO0Od       \n"
        "OOOOOOOOOOOOOO0OOOOOOOOOOOOOOOOOOxc'                             'lxkOOOOOOOOOOOOOOOO000000000OOOOOd       \n"
        "xxxkkkxxkkkkxxxxxxkkkxxxxxxxxkkkx:.                               .;dkkkkkkkkkkkkkkkkkkkkkkkkkkkkkko       \n\n\n");
}

void pti(){
    green();
    printf(
        "OkkkkkkkkkkOOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk\n"
        "00000000O0000000000OOOOO000OOOOO00OOOOO00OOOOO0OOOOO00000OOOOO0OO00000000OOOOOO000000000OOOOO000OOOO\n"
        "0000000000000000000OOOO000OOOOOOO000OO0000OOOOOOOOO000000OOOOOOOO00000000OO00OOOO0000000OOOOOOOOOOOO\n"
        "0000000000000000000OO000000OOO000000O00000OOOOOOOOOO0000000OOOOOO0000000OO0000OOO0000000OOOOOOOOOOOO\n"
        "0000000000000000000OOO00000000          2. PTI         O0000OO0OOOOOOOOOO00000OOOOOOOOOOOOOOOOOOOOOO\n"
        "00000000000000000000000000000000000000000000000000OOOOO0000OOOOOOO0OOOOOO0OOOOOOOOOOOOOOOOOOO000OOOO\n"
        "0000OO00000000000000000000000000000000000000000000000OOOO00OOOOOOOOOOO0OO0OOOOOOOOOOOOOOOOO000000OOO\n"
        "0OOOOO0000000000000000000000000000000000000O00000000OOOOOOOOOOOOOOOOOO00O00O000O0OO0OOOOOOOO000OOOOO\n"
        "0000000000000000000000000000O0000000000000OOOOO000000OOOOOOOO0000000OOOOOOOOOOOOOOO0OOOO00OO0000OOOO\n"
        "000000000000000000000000000OOOO0000000000000000O00000OOOOOOOOO000000000000OOOOOOO00000OO000OO0000OOO\n"
        "00000000000000O00000000000000000000000000000000OO0000OOOOOOOOOOO0000000OO00OOOOOOOdccxOOOO00OOO00OOO\n"
        "00000000OOOOOOOO000000000000000000000000000000OOOOOOOOO000OO00000000OO00OOOOOOkoc,. .'cxOOOOOOOO0OO0\n"
        "000000000OO00000000000000000000000000000000000OOOOOOO00000O000000000OOOOO0Okd:....... .cO00000000000\n"
        "0000000OO00000000000000000000000000000000000000OO00OO000000000000OOOOO0Oxl;'........';cxO00OOO000OOO\n"
        "0O00000OO00000000000000000000OO000000000000000OO000OO0000000OO0OOOOOOxo;.........;cxOOO0000OOOOOOOOO\n"
        "00000000000000000000000000000OOO000OOOOOOO00000000000OOOOOOOO00OOkdl:'.......';lxOOOOOOO000OOOOOOOOO\n"
        "000000000000000000000000000000000000OOOOOO0000OO0000000Oxl;;:odo:,........,:okO00OOOOO00000OOOOOOOO0\n"
        "00000000000000000000000OOO00OO0000000OOOOO000OOOOOO0Oxl;',;::;,. .'...';ldkO000000000000000OOOOOOOOO\n"
        "0000000000000000000OOO00000000OOOOOO00OOOO0OO00OOxdl;,,cdkOOOOkd;..':oxOO0000000000000000000OOOO0OOO\n"
        "0000000000000000000OOO0O000000OO0000OOO0OOOOOOdc;,,;cdOOOOOOOOOkc.;xOOOOO0000000000000000000000O0OOO\n"
        "00000000000000000000000OOO000OO0OOO0OOOO0Okdc,',cxkkO00OOO00OOOx;,dOOOO0OO00000000000000000000000000\n"
        "000000000000000000000000OO00000OOOOOOOOko:,,;lxO00OOOOOO0OOOOOkl''oOOO000OO0000000000000000000000OO0\n"
        "000000OO000000000000000OOO00000OOOOOko:,,:oxOOOOO000OOOOOOOko:'.'ckO00000OO0000O0000000000000000OOOO\n"
        "O00OOOOO000000000000000OOOO0OOOOOxl;;:cokOOOOOO00OOOOO0Odc,'.,cokOOO00O0OOO00OOOO00000000000000OOOOO\n"
        "OOOOOOOO00000000000OOO0OOOOOOkxl;',:dOOOOOOOOOO000OOkdl,..,cdkO000O000OOOOOOOOOO0000000000O000000OO0\n"
        "000OO00000000000000OOOOOOOOdc'..cdkO0OOOOOOOOOOOkol:'.':oxOOOOO000000000000OOO000000OOO0000000000000\n"
        "0000000000000000000000Okxl,. ...ck000OO0OOOOOko:'...;okO00000000000000000000000000000OO0000000000000\n"
        "00000000OO00000000OOkdc,,;;......:kO0OOOOOxc,..,cdxkOOOOOOO000000000000000000000000000OO000000000OO0\n"
        "OOO000000OO00000Oko:,,;lxOOl'. ...;xOOkd:'..,cdOO000OOOOOOO0OOO00000000000000000000000000000000OO000\n"
        "OOOO00000000000Ol,,cdkOOOOOOo'. ...'c:'..;lxOOOOOOOOOO0000O00OO00000000000000O00000OOO00000000OOOOOO\n"
        "O0000000000000Od',dOOO000OO0Od,. .. ..;okO0OOOOOOOOOO0000OOO0000000000000000OOO000000OOO00OO000OOOOO\n"
        "OOO000000000000d',xOOOOOOOOOOx:. .'cdkO00000OOOOOO00000000000000000000000000000000000OOO000OO0000OOO\n"
        "0OO0000000O0000Ol';xO000OOxl;..,cdk000000000000000000000000000000OO000O00000000000000000000OOOOOOOOO\n"
        "0000000000000000Oo;,cddoc,.';ldk000000O000000000000000000000000000OOOOO000000000000000000000OOO0OOOO\n"
        "0000000000000OOO00kc,'''';lxOO00000000000000000000000000000000000000OOO0000000000000000000OOOO000OOO\n"
        "0000000000OOOOO00O0OkddxkO0OO0000000000000OO000O0000000000000000000000OO00000000000O00000OOOO0O00OOO\n\n\n\n");
}
void pmln(){
    red();
    printf(
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000K\n"
        "XXXKKKXXXXXXXXXXXXXKKKKKKKKKKKKKKXKKXXXXXKKKKKKKKKXXXXXXXXXXKKKKKKKKKKKKXXXXXXXXXXXXKKXXXXXXXXXXXXXX\n"
        "XXXKKKXXXXXXXXXXXXXKKKKKKKKKKKKKKKKKKXKKKKKKKKKKKKKKKKKKKKKKKKKKKKXXXXXXXXXXXXXXXXXXXXKKKKKKKKKXXXKK\n"
        "XKKKKKXXXXXXXXXXXXXXXXKKKKKKK      3.  PMLN     KKKKKKKKKKKKKKKXXXXXXXXXXXXXXXXXXXKKKKXKKKKKKKKKKKKK\n"
        "XXKKKXXXXXXXXXXXXXXXXXXKKKXKKKKKKKKKKXXKKKKKKKKKKKKKKKKKKKKKKKKXXXXXXXXXXXXXXXXXXXXXXKKKXXXXXKKKKKKX\n"
        "XXXXXXXXXXXXXXXXXXXKKXXXXXXXKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKXXXXXXXXXXXXXXXXXXXXXXKKKKKXKKKKXXXXXXX\n"
        "XXXXXXXXXXXXXXXXKKKKKXXXKKKKKKKKKXXKKKKKKKKKKKKKKKKKKKKKKKKKKKKXXXXXXXXXXXXXXXXXXKKKKKKKKKKKKXXXXXXX\n"
        "XXXXKKKKXXXXXXXXKKKKKXXKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKXXXXXKKKKKKKKKXXXXXXXXXXXX\n"
        "XXXKKKKKKKXXXXXXXKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKXKKKKKKKKKKKKKKKKKKKKXXXXXKKKKKKKXXXXXXKXKXXXKK\n"
        "XXKKKKKKKKKXXXXXKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKXXXXKKKKKKKXXXXXXKKKKKKKXX\n"
        "XXXKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKXXXKKKKKKKKKKKKKKKKXXXXXXXKKXKK0xdx0KXKKXXXXXX\n"
        "KXXKKKKKKKKKKKKKKKKKKKKKK0OOkkxxxxkOOO000KKKKKKKKKXXXXXXXXXXXKKKKKKKKKKKXXXXXKKKK0kc,'.,;:oOKXXXXXXX\n"
        "KKKKKKKKKKKKKKXKK0kdollcccccclccccccccccccllloooooooddddddddollllc:;:clooodolccllc:...'cx:.;lkKKKXXX\n"
        "XKKKKKKKXKKKKK0xl:;;,;okxoldOkooO00xoxOdlxkxdddolodolloolccc;.....';lolc:;'',cdOOOOxdd:ckkxdc:lk0KKX\n"
        "XKKKKKKKKKKKOl;;cdlcdOKKx:oOxcoOKK0lck0ocxKOodOoo0XKxoOKxcoO0d:cddolk0Odoxkko:cx0O0KKOlckKXXKkc;o0KX\n"
        "XKKKKKKKKKKx:;::odco0K0xclk0l:kKKOdcd0Kd:oKOllkolkKKOc:xOo;:xOo:cdkocldOxllxOkllclOKOdl:o0XXKx,.,d0X\n"
        "KKKKKKKKKOc;lo:cdod0KKxcd0KOccO0xoold00dckKKdcxOlcdkKOlckKOocoOOxolxkdclkOdclk0OooOKk;.'lOKKKx:cc;lO\n"
        "XKKKKKKKk:;dk:;old0KKxlx00xlok0klxK0k0Ooo0XKdckKkc;o0XOlo0XKkco0K0dcd00dcdO0dlxKkldd::oold00xc;coc',\n"
        "XKKKKKKk:;dk:.:dokK0xokK0dlx0KKOdx0XX0xdOKXKdcxKOl:o0XKxcd0XXklxKXKOdd00xllk0do0Oc'.'codoooc,'....'c\n"
        "XKKKKKOc;do;'..lk0KkdOK0dlkKXKKOlo0XXKO0KKK0doOKOl:d0KXKxlkKXkldKXXXOdkKX0dlk0k0Kd'.'coooodl:,'',oOK\n"
        "XKKKK0d;lo,:l,';xKOdx0KxcdOO0K0dokKXK0KKXKKOkOKKxookKKXKxlkKKOocoOKXKkOKXXOoxKKKXO:,dKXXKKKKOocoOKKK\n"
        "KKKKKOc:o;,do;llck0O00xlx0dlkK0OOOO0000KXKOxOKXKOO0KKKXKOk0KKKKOo:o0kokKXXKkkKXXX0c;xKKKXXXKKKKKKKKK\n"
        "KKKXXO:co,:Ox:dx:l0XXKkk0kco00xlccclloxOKKxlxKKK0OkOOO000KKKKKKK0d:lxod0XXKKKKKXKd;cOKKKXXXXXXKKKKKK\n"
        "KKKXXk:cl,lOl:xOlcOKKKKKkld00l,',;:c:;:oOK0O0K000kxxdddolooooooool;.,cld0KKXXKXXKo,oKKKXXXXXXKKKXKKK\n"
        "KKKKKkclc,dk:cOKxcxKXKXKOOKKd;lkkxolc:::clodxkxk00KKKK0kxOOkxkkkxxdl,',:oOKKXK000d;o0KKKXXXXKKKKKKKK\n"
        "XKKXKd;c;;dl;dKKOldKXXXXKKKOccOKKKKKKKOkxolc:::::::clol:;ldo::occoxdc....;k0Oxoxkc:kKKKKXXXXXXXXXXXX\n"
        "XKKKk:,;,::;o0KKkccOX0kdxOOl:xKKKKKKKKKXKKKKK0OOkkxxxxdc.,lolc;..,ccllc:..ckdok0k:o0KKKKKXXXXXXKKKKK\n"
        "XKX0l;c,.':xxoxx;.'dK0kxkxc;dKKKKKKKKKKKKKKKKKKKKXXKXXKd:xKXK0o;lOKKKKX0l.cOKXXXOc:kKXXXXXXXXXXXKKKK\n"
        "XKkl:l:,:xOx;',,',':OKkdo::x0KKKKKKKKKKKKKKKKKKKKKKKXXKd:ok0Kd,c0XKXKKXXOl;o000KKx;c0XXXXXXXXXXXKKKK\n"
        "0d:co::xK0d,.,cdOO:'d00kc,dKKKKKKKKKKKKKKKKKKKKKKKKKXXKx,.:kk:;kKKKKKKXXX0d:::lOXKd:dKXXXXXXXXXXXXXX\n"
        "c:lc,:k0kc,:x0KXKk,.cOOo';kKKKKKKKKKKKKKKKKKKKKKKKKXXXXk'.;xo;oKKKKKKKXXXXKk:..cOK0lcOXXXXXXXXXXXXXX\n"
        "cl:'.;ol,:x0KXKX0l,oOkl''dKKKKKKKKKKKKKKKKKKKKKKKKKXXXXk'.cl,:kKKKKKKKXXXXXX0l..;xKx:o0KXXXXXXXXXXXX\n"
        ":;od;...'dKKXXK0o;o0K0l;d0KKKKKKKKKKKKKKKKKKKKKKKKXXXXKd':ko,l0KKKKXXKKKXXXXXKd'.,xOc:kKKXXXXXXXXXXX\n"
        "xOKk,...,xKXXXX0l;xKKk:lOKKKXKKKKKKKKKKXXKKKKKKXXXXXKKk:cOOlckKKKKXXXXXXXXXXXXKx,.;xd:ckKXXXXXXXXXXX\n"
        "XKKk,.:,,xKXKKXKOc;d00l:kKKKKXXKKKKKKKKKXKKKKXXXXXKXKKd,:kxcoKXKKKXXXXXXXXXXXXXKo',xKk::kXXXXXXXXKXX\n"
        "KKKd,,l;,xKXXXXXX0l;lOx;:x0KKKXXKKKKKKKKKKKKXXXXXXKKKKk:,dd:d00KKKKKKKKKKXXXXXKKk:,:x0k::dxxOKKKKKKK\n"
        "XX0l,:c;lOXXKXXXXXKd:cxko:cc:cd0KKKKKKKKKKKKXXXXXXKKKKKx;cdc;;;lkKKKKKKKKXXXXKKKK0kl;cdxooc,,o0XKKKK\n"
        "XKKkl:cd0KKKXXXXXXXKOocodo:'. .cOKKKKKKKKKKXXXXXKKKKKKKOl::::::,;xKKKKKKKKKKKKKKKKK0xc;cool;'l0XXKKK\n"
        "XXKKKKKKKKKKXXXXKXXXXKOooooc:clx0KKKKXXXKKKKKKKKKKKKKKKK0OdooooddOKXKKKXXKKXXXXXXKKKKK0kkOOOO0XXXXXX\n"
        "XXXXXXXXXXKKXXXKKXXXXXKKKKKKKKKXXXXKKXXXXKKKKKKKKKKKKKKKKKKKKXXXXXXXKKXXXXXXXXXXXXXKKXXXXXXXXXXXXXXX\n\n\n\n");
}


void miner(){
    black();
    printf(
        "       $$\\      $$\\           $$\\                                                   $$\\      $$\\ $$\\                               \n"
        "       $$ | $\\  $$ |          $$ |                                                  $$$\\    $$$ |\\__|                              \n"
        "       $$ |$$$\\ $$ | $$$$$$\\  $$ | $$$$$$$\\  $$$$$$\\  $$$$$$\\$$$$\\   $$$$$$\\        $$$$\\  $$$$ |$$\\ $$$$$$$\\   $$$$$$\\   $$$$$$\\  \n"
        "       $$ $$ $$\\$$ |$$  __$$\\ $$ |$$  _____|$$  __$$\\ $$  _$$  _$$\\ $$  __$$\\       $$\\$$\\$$ $$ |$$ |$$  __$$\\ $$  __$$\\ $$  __$$\\ \n"
        "       $$$$  _$$$$ |$$$$$$$$ |$$ |$$ /      $$ /  $$ |$$ / $$ / $$ |$$$$$$$$ |      $$ \\$$$  $$ |$$ |$$ |  $$ |$$$$$$$$ |$$ |  \\__|\n"
        "       $$$  / \\$$$ |$$   ____|$$ |$$ |      $$ |  $$ |$$ | $$ | $$ |$$   ____|      $$ |\\$  /$$ |$$ |$$ |  $$ |$$   ____|$$ |      \n"
        "       $$  /   \\$$ |\\$$$$$$$\\ $$ |\\$$$$$$$\\ \\$$$$$$  |$$ | $$ | $$ |\\$$$$$$$\\       $$ | \\_/ $$ |$$ |$$ |  $$ |\\$$$$$$$\\ $$ |      \n"
        "       \\__/     \\__| \\_______|\\__| \\_______| \\______/ \\__| \\__| \\__| \\_______|      \\__|     \\__|\\__|\\__|  \\__| \\_______|\\__|      \n"
        "                                                                                                                                   "
        " \n\n\n\n\n\n\n                                                                                           ");
}
/**
 * The main function of the program.
 *
 * @returns None
 */
void homePage(){
    int userChoice;
    homeScreen();
    reset();
    printf("\n\n\n\nSignup(1) or Login(2): ");
    scanf("%d", &userChoice);
    system("cls");
    switch (userChoice) {
        case 1:
            yellow();
            signUp();
            char checkLine[maxLength];
            printf("Enter your 13 digit CNIC: ");
            fgets(cnic, cnicLength, stdin);
            fgets(cnic, cnicLength, stdin);
            if (strlen(cnic) != 14) {
                puts("CNIC not found. Wrong Input entered");
                delay(2000);
                system("cls");
                homePage();
            }
            else{
                printf("Enter your Password( Should contain at least 8 characters): ");
                fgets(password, cnicLength, stdin);
                FILE* checkPresent;
                int flag = 1;
                checkPresent = fopen("C:\\Users\\TAHA\\Desktop\\Voting app FOP\\database.txt", "r");
                while (fgets(checkLine, maxLength, checkPresent)) {
                    if (strncmp(generateHash(cnic), checkLine,13) == 0) {
                        recordPresent();
                        flag = 0;
                        delay(3000);
                        system("cls");
                        homePage();
                        break;
                    }
                
                }
                fclose(checkPresent);
                if(flag == 1){
                    char nameHash[66];
                    strcpy(nameHash, generateHash(cnic));
                    FILE* fptr;
                    fptr = fopen("C:\\Users\\TAHA\\Desktop\\Voting app FOP\\database.txt", "a");
                    fprintf(fptr, "%s\n", nameHash);
                    fprintf(fptr, "%s\n", password);
                    fclose(fptr);
                    printf("\n\n\n\n");
                    successfullyRegistered();
                    reset();
                    printf("%s is your private key. Do not share it with anyone. Failure to do so will lead to all of your personal information being stolen.", generateHash(cnic));
                    strcpy(tempBlock->voterDetails[voteSign].voterPrivkey, generateHash(cnic));
                    strcpy(tempBlock->voterDetails[voteSign].cnic, cnic );
                    tempBlock->voterDetails[voteSign].voteStatus = 'N';
                    tempBlock->voterDetails[voteSign].isValidated = 'N';

                    voteSign++;
                    voteSign %= 3;
                    
                    
                    delay(10000);
                    system("cls");
                    homePage();
                }
            }
            break;
        case 2:
            login();
            char privKey[66];
            
            char line[maxLength];
            printf("Enter your Private Key: ");
            fgets(privKey,66 , stdin);
            fgets(privKey, 66, stdin);
            printf("Enter your Password: ");
            fgets(password, 40, stdin);
            FILE* logFile;
            logFile = fopen("C:\\Users\\TAHA\\Desktop\\Voting app FOP\\database.txt", "r");
            int flagCheckFile = 0;
            int mineChoice;
            char mineNow;
            while (fgets(line, maxLength, logFile)) {
                char tempLine[maxLength];
                
                if(strcmp(password,line) == 0 && strcmp(tempLine, privKey) == 0){
                    flagCheckFile = 1;
                    printf("Success loging in.......");
                    delay(3000);
                    system("cls");
                
                    int logChoice = 0;
                    do{
                        welcomeVoter();
                        voterPage();
                        reset();
                        printf("Enter your choice; Check Your Vote(1), Cast a Vote(2), Logout(3):");
                        scanf("%d", &logChoice);
                        while (getchar() != '\n');

                        if (logChoice == 1){
                            purple();
                            system("cls");
                            tempCheckBlock = Genesis;
                            int flag1 = 1;
                            for (int i = 0; i < blockNumber; i++){
                                for (int voteCount = 0; voteCount < 3; voteCount++){
                                    if (strncmp(tempCheckBlock->voterDetails[voteCount].voterPrivkey,  privKey,64) == 0 && tempCheckBlock->voterDetails[voteCount].voteStatus == 'Y') {
                                        printf("\n\nDETAILS OF VOTE\n\nName: %s\nCNIC: %s\nDomicile: %s\nVote Validated By the Miner: %c\n\n", tempCheckBlock->voterDetails[voteCount].name, tempCheckBlock->voterDetails[voteCount].cnic, tempCheckBlock->voterDetails[voteCount].domicile, tempBlock->voterDetails[voteCount].isValidated);
                                        if(tempCheckBlock->voterDetails[voteCount].voteTo == 1){
                                            printf("Vote Given To: MQM\n");
                                        }
                                        else if (tempCheckBlock->voterDetails[voteCount].voteTo == 2) {
                                            printf("Vote Given To: PTI\n\n");
                                        } else if (tempCheckBlock->voterDetails[voteCount].voteTo == 3) {
                                            printf("Vote Given To: PMLN\n");
                                        }
                                        // printf("Vote casted on %s", generateTimeStamp());
                                        flag1 = 0;
                                        delay(3000);
                                        break;
                                    }
                                }
                            
                                tempCheckBlock = tempCheckBlock->nextBlock;
                            
                            }
                            if(flag1 == 1)
                            {puts("You have Not Yet voted");}
                        } 
                        else if (logChoice == 2){
                            system("cls");
                            if(tempBlock->voterDetails[voteNum].voteStatus == 'N'){
                            mqm();
                            pti();
                            pmln();
                            reset();
                            printf("Enter Full Name: ");
                            fgets(name, 30, stdin);
                            printf("Enter your Domicile: ");
                            fgets(domicile, 30, stdin);
                            printf("Enter Who Do you want to vote for; MQM(1), PTI(2), PMLN(3): ");
                            scanf("%d", &voteTo);
                            while (getchar() != '\n');
                            voteNum++;
                            voteNum %= 3;
                            if (voteNum == 0) {
                                    voteNum = 3;
                                }
                                strcpy(tempBlock->voterDetails[voteNum-1].name, name);
                                strcpy(tempBlock->voterDetails[voteNum-1].domicile, domicile);
                                tempBlock->voterDetails[voteNum-1].voteTo = voteTo;
                                tempBlock->voterDetails[voteNum-1].voteStatus = 'Y';
                                
                                if (voteNum == 3) {
                                    strcpy(tempBlock->currentHash, generateHash(voterDetailsConcat()));
                                    if (tempBlock == Genesis) {
                                        strcpy(Genesis->prevHash, "0000000000000000000000000000000000000000000000000000000000000000");
                                    } else {
                                        strcpy(tempBlock->prevHash, tempBlock->prevBlock->currentHash);
                                    }
                                    tempBlock->blockNumber = blockNumber;
                                    tempBlock->minedStatus = 'N';
                                    strcpy(tempBlock->timestamp, generateTimeStamp());
                                    newBlock = (struct Block*)malloc(sizeof(struct Block));
                                    tempBlock->nextBlock = newBlock;
                                    tempBlock->nextBlock->prevBlock = tempBlock;
                                    tempBlock = tempBlock->nextBlock;
                                    blockNumber++;
                                }
                                system("cls");
                                voteRegistered();
                            }
                            else{
                                alreadyVoted();
                            }
                        } else if (logChoice == 3){
                            puts("Logging out....");
                            delay(3000);
                            system("cls");
                            homePage();
                            break;
                        }
                        delay(3000);
                        system("cls");

                    } while (userChoice != 3);
                    
                    break;
                }
                strcpy(tempLine, line);
            }
            if (flagCheckFile == 0){
                noRecord();
                delay(3000);
                system("cls");
                homePage();
            }
            fclose(logFile);
            break;
        case 3:
            
            while(1){
                miner();
                minerBlock = Genesis;
                printf("\nWhat do you want to do? Check for available Blocks to mine(1), Logout(2): ");
                scanf("%d", &mineChoice);
                int mineFlag = 1;
                switch(mineChoice){
                    case 1:
                        for (int mineCount = 0; mineCount < blockNumber - 1; mineCount++){
                            if(minerBlock->minedStatus == 'N'){
                                mineFlag = 0;
                                printf("Block Available to Mine\n\nBlock Details:");
                                red();
                                printf(
                                    "+--------------------------------------------------------------------------------------------------------------+\n"
                                    "|                                                                                                              |\n"
                                    "|      Block Number: %d                                                                                        |\n",
                                    minerBlock->blockNumber);
                                printf(
                                    "|                                                                                                              |\n"
                                    "|      Current Hash: %s                          |\n",
                                    minerBlock->currentHash);
                                printf(
                                    "|                                                                                                              |\n"
                                    "|      Previous Hash: %s                                                                                       |\n",
                                    minerBlock->prevHash);
                                printf(
                                    "|                                                                                                              |\n"
                                    "+--------------------------------------------------------------------------------------------------------------+\n\n\n");
                                
                                green();

                                printf("Mining in progress...");
                                delay(3000);

                                mineBlock(forMiner(minerBlock));
                                printf("Succesfully Mined! All User votes validated.\n\nNew Block Details\n\n");
                                printf(
                                    "+--------------------------------------------------------------------------------------------------------------+\n"
                                    "|                                                                                                              |\n"
                                    "|      Block Number: %d                                                                                        |\n",
                                    minerBlock->blockNumber);
                                printf(
                                    "|                                                                                                              |\n"
                                    "|      Nonce: %d                                                                                                |\n",
                                    minerBlock->nonce);
                                printf(
                                    "|                                                                                                              |\n"
                                    "|      Current Hash: %s                          |\n",
                                    minerBlock->currentHash);
                                printf(
                                    "|                                                                                                              |\n"
                                    "|      Previous Hash: %s                                                                                       |\n",
                                    minerBlock->prevHash);
                                printf(
                                    "|                                                                                                              |\n"
                                    "+--------------------------------------------------------------------------------------------------------------+\n\n\n");
                                minerBlock->voterDetails[0].isValidated = 'Y';
                                minerBlock->voterDetails[1].isValidated = 'Y';
                                minerBlock->voterDetails[2].isValidated = 'Y';
                                minerBlock->minedStatus = 'Y';
                                                        }
                            
                            minerBlock = minerBlock->nextBlock;
                        }
                        if (mineFlag == 1){
                            green();
                            printf("No work to do for now. Check Back later to Validate Blocks\n\n");
                            delay(3000);
                            system("cls");
                        }
                        break;
                    case 2:
                        printf("Logging out....");
                        delay(3000);
                        system("cls");
                        homePage();
                        break;
                        
                    }
            }
                
            
        default:
            puts("Wrong Input Entered");
    }
}
int main() {
    int choice;
    //Mem alloc for Hash
    memoryHash = (char*)malloc(65);
    concatText = (char*)malloc(maxLength);
    tempConcat = (char*)malloc(maxLength);
    Genesis = malloc(sizeof(struct Block));
    tempBlock = Genesis;
    tempBlock->prevBlock = NULL;
    voteNum = 0;
    blockNumber = 1;
    homePage();

    

    return 0;
}