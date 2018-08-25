#ifndef CPU_H
#define CPU_H

// TODO Update if more information is needed
typedef struct {
    unsigned char intelSignature;   // Flag if cpu vendor equals 'GenuineIntel' 
    unsigned int cpuInfo_maxBasic;  // Max basic cpuid request code
    unsigned int cpuInfo_maxExt;    // Max basic cpuid extended code
    unsigned char HTT;              // CPU supports Hyper-Threading Technology
    unsigned char TM;               // CPU supports Thermal Monitor
} cpuInfo_t;

// TODO eventually upate to array for multi core
cpuInfo_t cpuInfo_global;

/*
 * Check if CPUID instruction is available.
 */ 
extern int checkCPUID(void);

#endif