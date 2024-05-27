# Cpp-storage-test-task
Test task for position Software Development Engineer for Data Storage systems (C++)

## Использование

```bash
tape_sorter input_tape output_tape [config_path]
```

### Формат ленты
Лента должна представлять собой текстовый файл с числами разделенными пробелами

<details>
<summary>Пример ленты</summary>

```4 5 1 8```
</details>

### Конфиги
Используется формать ini. 

Конфиг должен содержать параметры 

delays: 
- read_write (uint64_t, в наносекундах)
- move (uint64_t, в наносекундах)

memory_limit: 
- m (uint64_t, в байтах, должно быть больше или равно 8. Параметр отвечает за потребляемую программой память)

<details>
<summary>Пример конфига</summary>

```ini
[delays]
; delays in nanoseconds
read_write=100
move=100
[memory_limit]
; program will use m + constant bytes of RAM
m=32
```
</details>
