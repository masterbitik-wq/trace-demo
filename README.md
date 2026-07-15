# trace-demo
# Трассировка системных вызовов

Программа демонстрирует использование системных вызовов: getpid, gettimeofday, open, write, close, stat, read.

## Сборка
make

## Трассировка
strace -o trace.log ./trace_demo
