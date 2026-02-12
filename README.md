# EDRStress

Консольный инструмент для **тестирования** EDR и AV систем на платформе Windows.

## Принцип работы

EDRStress взаимодействует с Native API Windows через модуль ntdll.dll, минуя высокоуровневые WinAPI-обертки. 
Инструмент демонстрирует классическую технику эскалации привилегий с последующей имитацией критической системной ошибки:

1. `RtlAdjustPrivilege` — включение привилегии `SE_SHUTDOWN_PRIVILEGE`
2. `NtRaiseHardError` — инициация фатальной системной ошибки

## Целевая картина детекта

**EDR-системы** (например, [ProcessesLaboratory](https://github.com/MyAngelWhiteCat/ProcessesLaboratory)) 
должны обнаружить аномальные вызовы Native API в контексте процесса, отследить включение критических привилегий 
и предотвратить развитие атаки до стадии системного сбоя.

**AV-решения** должны детектировать импорты недокументированных функций (`RtlAdjustPrivilege`, `NtRaiseHardError`)

## Сборка

```bash
git clone git@github.com:MyAngelWhiteCat/EDR-Stress.git
cd EDR-Stress
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

Usage:

```
./bsod_thrower
```

Инструмент предназначен исключительно для легитимного тестирования средств защиты в контролируемых средах.
Пожалуйста, для тестирования, используйте виртуальную машину.
