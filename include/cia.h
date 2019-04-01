#ifndef _CIA_H_
#define _CIA_H_

#include <cia_regdef.h>

typedef struct CIA *const CIA_t;

#define CIAA ((volatile CIA_t)0xbfe001)
#define CIAB ((volatile CIA_t)0xbfd000)

extern volatile CIA_t ciaa;
extern volatile CIA_t ciab;

/* Both CIAA & CIAB have Timer A & Timer B */
#define TIMER_ANY -1UL
#define TIMER_CIAA_A 0
#define TIMER_CIAA_B 1
#define TIMER_CIAB_A 2
#define TIMER_CIAB_B 3

/* CIA timers resolution is E_CLOCK (in ticks per seconds). */
#define E_CLOCK 709379

/* Maximum delay is around 92.38ms */
#define TIMER_MS(ms) ((ms) * E_CLOCK / 1000)
#define TIMER_US(us) ((us) * E_CLOCK / (1000 * 1000))

/* Procedures for handling one-shot delays with high resolution timers. */
void TimerInit(void);
int AcquireTimer(unsigned num);
void ReleaseTimer(unsigned num);
void WaitTimer(unsigned num, uint16_t delay);

/* 24-bit frame counter offered by CIA A */
uint32_t ReadFrameCounter(void);
void SetFrameCounter(uint32_t frame);

/* 24-bit line counter offered by CIA B */
void LineCounterInit(void);
void LineCounterKill(void);
void LineCounterWait(uint32_t lines);

/* You MUST use following procedures to access CIA Interrupt Control Register!
 * On read ICR provides pending interrupts bitmask clearing them as well.
 * On write ICR masks or unmasks interrupts. If writing 1 with CIAIRCF_SETCLR to
 * a bit that is enabled causes an interrupt. */

/* ICR: Enable, disable or cause interrupts. */
uint8_t WriteICR(CIA_t cia, uint8_t mask);

/* ICR: sample and clear pending interrupts. */
uint8_t SampleICR(CIA_t cia, uint8_t mask);

#endif
