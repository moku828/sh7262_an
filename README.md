# SH7262 Application Notes
## Summary
SH7262アプリケーションノート.pptx

## blink(Lチカ)
### Build
    docker run --rm -it -vC:\test\sh7262_an\blink:/workspace sh-tools/make
### Run
HJ-LINK/USB Debugger for SH7262起動  
Download program...からblink.elf選んでPC:1C000000に書き換えてRun  

## lcdclock(LCDクロック)
### Build
    docker run --rm -it -vC:\test\sh7262_an\lcdclock:/workspace sh-tools/make
### Run
HJ-LINK/USB Debugger for SH7262起動  
Download program...からlcdclock.elf選んでPC:1C000000に書き換えてRun  
