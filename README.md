# trunos


### Инструкции по сборке runos:
- [Подготовка](https://github.com/ARCCN/runos/blob/master/README.md)
- Сама сборка:
    ```ssh
    $ mkdir -p build; cd build
    $ cmake -DCMAKE_BUILD_TYPE=Release ..
    $ make prefix -j2
    $ make -j2
    ```
### Инструкции по запуску
- Запуск runos
	```ssh
	debug_run_env.sh
	build/runos
	```
- Запуск тестов
    ```ssh
    sudo /tests/run.py config report
    ```
Отчёт по потокам данных будет сгенерирован в test/results/report
