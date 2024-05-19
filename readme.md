# Minimal project for SiLabs EFR32FG23A010F256GM48

- Gecko SDK 4.2.2 (GSDK) is included with all unnecessary things stripped (directory: gecko-sdk)
- linker script from GSDK has been adjusted for EFR32FG23A010F256GM48 (directory: ld)
- src directory includes all files needed to build the project    
- hal_st_lld.c/h implements LETIMER0 as "systick", just to prove that interrrupts work
- ef32fg23.jdebug is a project file for Ozone Debugger
- Ozone Debugger can show periperihals, for what svd file is needed (directory: svd/EF32FG23)
- used makefiles and scripts from ChibiOS with minimal changes (directory: mk)
