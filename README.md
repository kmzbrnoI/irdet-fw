# IR Detector firmware

TODO

## Build & requirements

This firmware is developed in C language, compiled via `avr-gcc` with help
of `make`. You may also find tools like `avrdude` helpful.

Hex files are available in *Releases* section.

## Programming

PCB contains standard AVR ISP programming connector.

```bash
$ make
$ make fuses
$ make program
```

## Author's toolkit

Text editor + `make`. No more, no less.

## Authors

 * Jan Horacek ([jan.horacek@kmz-brno.cz](mailto:jan.horacek@kmz-brno.cz))

## License

This application is released under the [Apache License v2.0
](https://www.apache.org/licenses/LICENSE-2.0).
