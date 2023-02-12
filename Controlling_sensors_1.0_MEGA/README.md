# Lendo os sensores LEGO EV3

Com o intuito validar o controle dos sensores LEGO EV3 utilizando outras plataformas de prototipação, testes iniciais foram conduzidos valendo-se do Arduino MEGA 2560. A partir do sucesso dessa etapa inicial, o algoritmo foi aprimorado, a fim de que pudesse ser considerado um MVP (minimum viable product), estando disponível para o público na versão 1.0.

> O que o código faz ?

Realiza a leitura dos sensores de toque, cor e infravermelho, sendo possível trocar o sensor conectado em tempo de execução do programa. Além disso, exclusivamente para o **sensor de cor**, é possível mudar o modo de operação entre refletância (0), intensidade da luz ambiente (1) e cor (2). Para tal, basta enviar o número do modo desejado pelo Monitor Serial. Ademais, as leituras do **sensor infravermelho** são realizadas apenas no modo de proximidade/distância. Por fim, uma verificação do *checkbyte* é realizada nos pacotes de dados *Data Message* a fim de validar as leituras enviadas. 


> O que o código não faz ?

O sensor de infravermelho suporta outros modos — os quais funcionam em conjunto com o IR beacon —, contudo a leitura desses modos não foi implementada devido à ausência do IR beacon para testes. Por último, caso aconteçam sucessivos erros de *checkbyte*, uma rotina para tratá-los — por exemplo, reiniciar o sensor — não foi concretizada.

## Instruções 

Após clonar esse repositório, execute os seguinte passos: 
* Abrir o arquivo **.ino** na Arduino IDE.
* Compilar e carregar para a placa selecionada.
* Configurar o Monitor Serial para o baudrate de 57600bps e para NO LF (NO LINE FEED). 