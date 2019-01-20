Bluetooth - SAIL
=================
```
Sensor Bluetooth para o sistema SAIL. 

Usando a placa ESP32, o sistema analisa o ambiente a procura de dispositivos que estejam com o 
bluetooth ativado, alimentando um sistema maior para identificação de possíveis usuários. 

O sensor busca por endereços MAC associados aos dispositivos encontrados no ambiente, os quais são 
armazenados em uma lista contendo todos os endereços escaneados durante um curto período de tempo. 
Os mesmos são estruturados em formato JSON, para então serem encaminhados ao servidor local, que irá 
repassar ao servidor principal.
```
