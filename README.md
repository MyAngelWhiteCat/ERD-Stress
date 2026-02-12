Консольный инструмент для **тестирования** EDR и AV систем, взаимодействует с ядром OS Windows через модуль ntdll.dll.
Реализует вызовы функций ядра RltAdjustPrivilge для эскалации привелегий, после чего вызывает NtRaiseHardError для вызова фатальной системной ошибки с последующим BSOD.

Задача EDR систем, таких как [лабаратории процессов](https://github.com/MyAngelWhiteCat/ProcessesLaboratory) - утилиты для динамического исследования активных процессов и выявления активнности вредоносов,
состоит в том, чтобы обнаружить взаимодействие с модулем ntdll.dll, обранужить вызов RtlAdjustPrivilege, отловить NtRaiseHardError и не допустить аварийную перезагрузку.

Задача AV систем - обнаружить в PE заголовках информацию об загрузке модуля ntdll.dll, использование функций ядра и особенно важно - обнаружить взаимодействие с NtRaiseHardError.

Building:

```
git clone git@github.com:MyAngelWhiteCat/ERD-Stress.git
cd ERD-Stress
mkdir build
cd build 
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

Usage:

```
./bsod_thrower
```

