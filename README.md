# sdfr

Программный рендерер параметрической модели здания на C11 и NASM: raymarching
по полям расстояний (SDF) на CPU. Версия 0.2.0, в разработке.

## Сборка и запуск

Требуется x86-64 Linux или WSL 2.
Команды выполняются из корня репозитория.

```sh
sudo apt install -y build-essential
make
./sdfr test.ppm
```

- `./sdfr test.ppm` — тестовый кадр 640x360 в `test.ppm`.
