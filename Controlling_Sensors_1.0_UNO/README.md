# Lendo os sensores LEGO EV3 com Arduino UNO

O algoritmo que inicialmente foi construído pensando na plataforma do ATMEGA 2560, isto é, Arduino MEGA, foi portado para o ATMEGA 328p, o qual integra o Arduino UNO. Tal adaptação mostra-se benéfica, pois torna acessível as funcionalidades do projeto, uma vez que o Arduino UNO é a placa mais comercializada e mais utilizada, fato que democratiza o uso do presente projeto por outras pessoas. 

> O que o código faz ?

Realiza a leitura dos sensores de toque, cor e infravermelho, sendo possível trocar o sensor conectado em tempo de execução do programa. Além disso, **exclusivamente para o sensor de cor**, é possível mudar o modo de operação entre refletância (0), intensidade da luz ambiente (1) e cor (2). Para tal, basta enviar o número do modo desejado pelo Monitor Serial. Ademais, as leituras do sensor infravermelho são realizadas apenas no modo de proximidade/distância. Por fim, uma verificação do checkbyte é realizada nos pacotes de dados *Data Message* a fim de validar as leituras enviadas.

> O que o código não faz ? 

O sensor de infravermelho suporta outros modos — os quais funcionam em conjunto com o *IR beacon* —, contudo a leitura desses modos não foi implementada devido à ausência do *IR beacon* para testes. Por último, caso aconteçam sucessivos erros de checkbyte, uma rotina para tratá-los — por exemplo, reiniciar o sensor — não foi concretizada.

## Detalhes importantes 

A porta de Hardware Serial nativa do ATMEGA328p não foi utilizada para a comunicação com os sensores, sendo que foi preservada para exportar, de maneira facilitada, as leituras deles. Assim, foi preciso implementar uma comunicação UART com portas virtuais, isto é, por meio de software. Optou-se pela lib **AltSoftSerial** — acesse a [referência oficial](https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html) — ao invés da lib que é distribuída em conjunto com a Arduino IDE: SoftwareSerial. Tal preferência deu-se em função da menor latência da lib AltSoftSerial em comparação com a SoftwareSerial, de forma que a primeira possui latência de 2-3&mu;s e a segunda de 174&mu;s. 

Todavia, o estado das portas, utilizadas pela UART virtual, antes da execução do método **begin()** não é completamente restaurado pelo método **end()** em ambas as libs. Isso interfere diretamente na leitura do pino 1 da placa adaptadora, o qual realiza a identificação do tipo do sensor. O sensor de toque é o único afetado, pois seu resistor interno — que garante sua identificação — é ligado ao TX da UART virtual, o qual não é devidamente tratado pelo método end(). Sendo assim, uma variação de 5 a 10% é percebida na leitura analógica que detecta a conexão do sensor de toque. Tal questão já foi solucionada no código, como exemplificado abaixo. 
```
while(analogRead(ID_sensor) >= 80 && analogRead(ID_sensor) <= 100){}
```

Por fim, como a lib AltSoftSerial utiliza o timer de 16 bits, a temporização do envio do NACK (0x02) ao sensor passou a ser realizada pela função millis() e por uma lógica associada. 

## Instruções 
Após clonar esse repositório, execute os seguinte passos: 
* Abrir o arquivo **.ino** na Arduino IDE.
* Instalar, pela Arduino IDE, a lib AltSoftSerial v1.4 (by Paul Stoffregen)
* Compilar e carregar para a placa selecionada.
* Configurar o Monitor Serial para o baudrate de 57600bps e para NO LF (NO LINE FEED). 
