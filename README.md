# vlsdn


### Инструкции по сборке runos:
- [Подготовка](https://github.com/ARCCN/runos/blob/master/README.md)
- Сама сборка:
    ```ssh
    $ mkdir -p build; cd build
    $ cmake -DCMAKE_BUILD_TYPE=Release ..
    $ cd ..
    $ make prefix -j2
    $ make -j2
    ```
### Инструкции по запуску
- Запускаем runos
    ```ssh
    build/runos
    ```
- Запускаем mininet
    ```ssh
    sudo mn --custom path/topology.py --topo mytopo --switch user --controller remote,port=6653
    ```

