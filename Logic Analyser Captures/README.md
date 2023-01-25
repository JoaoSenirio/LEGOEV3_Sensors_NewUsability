## Pacotes de dados e comunicação UART

Nesta seção, será explorado mais sobre os pacotes de dados trafegados entre os sensores digitais e o *brick*, além das característica e da dinâmica da comunicação UART entre eles. 

As figuras abaixo são referentes aos arquivos **.sal**, sendo extraídas do programa Logic 2 da Saleae, e ilustram os pacotes de dados enviados pelos sensores digitais no momento que transmitem toda configuração inicial ao *brick*. Já os arquivos **.xlsx** correspondem a esses pacotes de dados interpretados, com a informação de cada *byte* devidamente explicada, de maneira a facilitar a compreensão. 

Os referidos pacotes de dados carregam 4 principais tipos de menssagem, sendo eles *System Message*, *Command Message*, *Data Message* e *Info Message*. Todos eles possuem ao menos um *byte*, como é o caso do *System Message*, intitulado **Message byte**. No caso do *Command Message* e *Data Message* ainda há uma quantidade de *bytes* variável, intitulada **Payload**, a qual carrega a informação propriamente dita. Por último, a categoria *Info Message* possui um *byte* adicional, chamado de **Info byte**, situado entre o **Message byte** e o **Payload**. Todos os 4 tipos de menssagem encerram com um *checkbyte*, o qual é calculado pela operação XOR (OU EXCLUSIVO) entre todos os *bytes* que compõem a menssagem e um byte específico: 0xFF.

Toda vez que o sensor realiza uma leitura diferente da anterior, dentro das limitações de velocidade de leitura dele e de mudança da superfície, ele envia dados ao *brick*. Ademais, sempre que o *brick* manda NACK (0x02) ao sensor, que se enquadra em *System Message*, além de manter a comunicação estável, esse devolve um valor de leitura realizada. 


