# Pacotes de dados e comunicação UART

Nesta seção, será explorado mais sobre os pacotes de dados trafegados entre os sensores digitais e o *brick*, além das característica e da dinâmica da comunicação UART entre eles. 

As figuras abaixo são referentes aos arquivos **.sal**, sendo extraídas do programa Logic 2 da Saleae, e ilustram os pacotes de dados enviados pelos sensores digitais no momento que transmitem toda configuração inicial ao *brick*. Já os arquivos **.xlsx** correspondem a esses pacotes interpretados, com a informação de cada *byte* devidamente explicada, de maneira a facilitar a compreensão. 

Os referidos pacotes de dados carregam 4 principais tipos de menssagem, sendo eles *System Message*, *Command Message*, *Data Message* e *Info Message*. Todos eles possuem ao menos um *byte*, como é o caso do *System Message*, intitulado **Message byte**. No caso do *Command Message* e *Data Message* ainda há uma quantidade de *bytes* variável, intitulada **Payload**, a qual carrega a informação propriamente dita. Por último, a categoria *Info Message* possui um *byte* adicional, chamado de **Info byte**, situado entre o **Message byte** e o **Payload**. Todos os 4 tipos de menssagem encerram com um *checkbyte*, o qual é calculado pela operação XOR (OU EXCLUSIVO) entre todos os *bytes* que compõem a menssagem e um byte específico: 0xFF.

*Data Message* é o pacote de dados que carrega as leituras feitas pelos sensores diretamente para o *brick*. Seu **Message byte** possui a seguinte composição: 0b11LLLMMM, na qual MMM é o modo no qual o sensor se encontra e 2<sup>0bLLL</sup> é o tamanho, em bytes, dos dados enviados. Na sequência há o **Payload**, no qual situa-se as leituras realizadas, e por último é enviado o checkbyte, que segue o mesmo formato anteriormente descrito. Para mudar o modo de leitura do sensor, é necessário que o *brick* envie determinado pacote de dados, intitulado **Command Message**, a fim de que a troca seja bem sucedida. Tal comando deve seguir a seguinte estrutura: **Message byte** (0x43), **Payload** (modo desejado formatado para o tipo byte) e *checkbyte*.

Ademais, toda vez que o sensor realiza uma leitura diferente da anterior, dentro das limitações de velocidade de leitura dele e de mudança da superfície, ele envia dados ao *brick*. Por fim, sempre que o *brick* manda NACK (0x02) ao sensor — no intervalo de, no mínimo, 100ms e de, no máximo, 1500ms —, além de manter a comunicação estável, esse devolve um valor de leitura realizada a partir da solicitação. 


