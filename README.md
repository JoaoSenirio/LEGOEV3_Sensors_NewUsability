# Sensores Lego EV3: nova possibilidade de uso 

## Resumo 

## Motivação

## Detalhes do processo

Inicialmente, em busca de informações técnicas sobre os sensores e sobre toda a coleção LEGO MINDSTORM EV3, foi encontrada ampla documentação — nomeada Developer Kit — fornecida pela própria LEGO, que versa sobre *Firwmare, Hardware e Comunicação*, podendo ser acessada [neste link.](https://education.lego.com/en-us/product-resources/mindstorms-ev3/downloads/developer-kits) As informações mais relevantes para a execução do projeto encontram-se na seção *Hardware*, a qual está anexada ao repositório.

Para o desenvolvimento do projeto, os sensores de toque, luz/cor e infravermelho foram usados nos testes e nas etapas seguintes. Com o intuito de estabelecer conexão física com os sensores, para assim compreender a comunicação entre eles e o *brick* e mais tarde realizá-la sem o *brick*, foi preciso a construção de uma placa adaptadora, a qual contou com o conector específico da coleção EV3: 6 *wire* RJ-12 *right side*. No exterior, tal conector pode ser facilmente encontrado em lojas de varejo, como o AliExpress, porém, no Brasil, apesar da sua comercialização ser mais rara, pode ser encontrado em lojas como a [RoboCore.](https://www.robocore.net/) A placa adaptadora, confeccionada em placa perfurada, surgiu como alternativa à protoboard, uma vez que a robustez e a confiabilidade das ligações na nova montagem cessaram as interferências e a perda de dados.

A placa adaptadora ainda conta com resistor de *pull-up* no pino 1 e de *pull-down* no pino 6. O pino 1 é responsável pela identificação da conexão do sensor e a qual tipo ele pertence, isto é, permite a diferenciação entre o estado de disconectado, de sensor simples conectado ou de sensor digital conectado. Sendo assim, por meio das ligações internas dos sensores relativas ao pino 1 associadas ao resistor de *pull-up* externo, são percebidas distintas tensões entre cada estado — 5 volts para disconectado, 0.42 volts para sensor simples conectado e 0 volts para sensor digital conectado —, as quais, quando tratadas por portas analógicas ou por conversores A/D, permitem a identificação dos sensores. As leituras feitas por eles são enviadas ao controlador principal por meio do pino 6, sendo que o terminal é utilizado para esse fim tanto pelo sensor simples quanto pelo digital. Todavia, o sensor de toque — como sensor simples —, quando não detecta nenhum contato, deixa o pino 6 flutuando, ou seja, sem nenhuma referência de tensão. Visando contornar tal problema, sem promover nenhum tipo de interferência na comunicação do sensor digital, implementou-se um resistor de *pull-down* externo ao pino 6. 

Com a placa montada, o mapeamento dos pinos dela foi realizado seguindo os esquemáticos dos sensores — visando identificar pinos como GND, VCC e UART TX/RX. Com isso, foi possível conectar os sensores digitais ao analisador lógico USB, semelhante a esse do [link,](https://www.usinainfo.com.br/testadores-e-medidores-diversos/analisador-logico-24mhz-8ch-al24-2691.html) permitindo conhecer/analisar os pacotes de dados enviados por eles. Tais pacotes foram interpretados com o auxílio do *software* [Logic 2](https://www.saleae.com/downloads/) (da Saleae), da documentação oficial da LEGO e da documentação do projeto LeJOS, o qual conduziu uma análise do [Protocolo dos Sensores UART.](https://sourceforge.net/p/lejos/wiki/UART%20Sensor%20Protocol/) Maiores detalhes sobre a comunicação UART, capturas do analisador lógico e a interpretação dos pacotes encontram-se na [devida pasta.](https://github.com/JoaoSenirio/LEGOEV3_Sensors_NewUsability/tree/main/Logic%20Analyser%20Captures)

A partir de toda informação até aqui coletada, iniciou-se a programação de um microcontrolador com o intuito de captar e exportar as leituras feitas pelos sensores LEGO EV3. Inicialmente, optou-se pelo ATMega 2560 — embarcado na plataforma do Arduino Mega — para construir o algoritmo principal, uma vez que tal microcontrolador possui inúmeros recursos que facilitam a primeira etapa de codificação, tais como 4 UARTs, 6 timers, além de extensa memória. Peculiaridades técnicas dessa aplicação inicial encontram-se na [respectiva pasta.](https://github.com/JoaoSenirio/LEGOEV3_Sensors_NewUsability/tree/main/Controlling_sensors_1.0_MEGA) A título exemplo, um vídeo demonstrando o projeto em funcionamento foi produzido. A seguir, o algoritmo foi trabalhado a fim de reduzir o uso de memória e melhorar seu desempenho, de forma que foi possível portá-lo para o ATMega 328p — embarcado no Arduino UNO. Um vídeo de demonstração também foi produzido e detalhes técnicos dessa etapa podem ser conferidos na [devida pasta.](https://github.com/JoaoSenirio/LEGOEV3_Sensors_NewUsability/tree/main/Controlling_Sensors_1.0_UNO) 

## Próximos passos 
## Conclusão