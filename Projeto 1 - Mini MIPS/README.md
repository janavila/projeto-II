<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Relatório: Implementação de Simulador MiniMIPS em Linguagem C</title>
</head>
<body>
    <h1>Relatório: Implementação de Simulador MiniMIPS em Linguagem C</h1>
    <p><strong>Autor:</strong> Gustavo Oliveira, Jansen Avila, João Eduardo</p>
    <p><strong>Data:</strong> 25 de abril de 2024</p>
    
<h2>Introdução</h2>
    <p>Este relatório descreve o desenvolvimento e a implementação de um simulador MiniMIPS básico em linguagem C. O simulador foi criado como parte de um projeto acadêmico para demonstrar conceitos de arquitetura de computadores e programação de sistemas. O objetivo principal do simulador é permitir aos usuários carregar um conjunto de instruções MiniMIPS a partir de um arquivo, executar essas instruções e visualizar o estado da memória de instruções, memória de dados e registradores MiniMIPS.</p>
    
<h2>Estrutura do Código</h2>
    <h3>Inclusão de Bibliotecas</h3>
    <p>As bibliotecas padrão <code>&lt;stdio.h&gt;</code>, <code>&lt;stdlib.h&gt;</code> e <code>&lt;string.h&gt;</code> são incluídas para fornecer funcionalidades essenciais para entrada/saída, alocação de memória dinâmica e manipulação de strings, respectivamente. Além disso, é incluído o arquivo de cabeçalho <code>"reader.h"</code> para as declarações de funções relacionadas à leitura e armazenamento de instruções.</p>

<h3>main.c</h3>
    <p>O arquivo <code>main.c</code> contém a função principal do simulador MiniMIPS. Ele implementa um loop de execução que exibe um menu para o usuário e executa a operação escolhida.</p>
    
<h3>reader.h e MiniMIPS.c</h3>
    <p>O arquivo de cabeçalho <code>reader.h</code> declara as estruturas de dados e as assinaturas de funções necessárias para a leitura e manipulação de instruções MiniMIPS. O arquivo <code>MiniMIPS.c</code> implementa essas funções.</p>

<h2>Exemplo de Uso do Simulador MiniMIPS</h2>
<h3>Carregar Memória de Instruções</h3>
<p>Para carregar um conjunto de instruções na memória do simulador MiniMIPS, o usuário pode selecionar a opção 'Carregar Memória' no menu principal. Isso permite que o usuário carregue um arquivo contendo instruções MiniMIPS em formato binário ou assembly.</p>
    
<h3>Imprimir Memória de Instruções</h3>
    <p>Para visualizar as instruções atualmente carregadas na memória do simulador MiniMIPS, o usuário pode selecionar a opção 'Imprimir Memória' no menu principal. Isso exibirá as instruções armazenadas na memória, permitindo ao usuário verificar as instruções carregadas.</p>
    
<h3>Executar Programa</h3>
    <p>Para executar o programa carregado na memória do simulador MiniMIPS, o usuário pode selecionar a opção 'Executar Programa' no menu principal. Isso iniciará a execução do programa, seguindo as instruções carregadas na memória até que o programa termine ou uma instrução de parada seja encontrada.</p>
    
<h3>Executar uma Instrução</h3>
    <p>Para executar uma única instrução do programa carregado na memória do simulador MiniMIPS, o usuário pode selecionar a opção 'Executar Instrução' no menu principal. Isso executará a próxima instrução na sequência de instruções, permitindo ao usuário observar o efeito de uma instrução específica no estado do simulador.</p>
    
<h3>Salvar Estado Atual</h3>
    <p>Para salvar o estado atual do simulador MiniMIPS, incluindo o conteúdo da memória de instruções, memória de dados e valores dos registradores, o usuário pode selecionar a opção 'Salvar Estado' no menu principal. Isso permite que o usuário salve o estado atual do simulador para posterior análise ou restauração.</p>
    
<h3>Outras Operações</h3>
    <p>Além das operações mencionadas acima, o simulador MiniMIPS também oferece funcionalidades adicionais, como imprimir registradores, imprimir todo o estado do simulador e voltar uma instrução. Essas operações fornecem ao usuário controle total sobre a execução e visualização do programa carregado na memória do simulador.</p>

<h2>Resultados e Discussões</h2>
    <h3>Teste de Carga e Execução de Instruções</h3>
    <p>Durante os testes de carga e execução de instruções, verificou-se que o simulador MiniMIPS foi capaz de carregar corretamente um conjunto de instruções MiniMIPS a partir de um arquivo e executá-las de acordo com as especificações do conjunto de instruções...</p>
    
<h3>Teste de Funcionalidades Específicas</h3>
    <p>Foram realizados testes para avaliar funcionalidades específicas do simulador MiniMIPS, como a execução de uma única instrução, a impressão da memória de instruções e a visualização do estado dos registradores...</p>
    
<h3>Limitações e Possíveis Melhorias</h3>
    <p>Durante os testes, algumas limitações foram identificadas no simulador MiniMIPS, como a falta de suporte para instruções de ponto flutuante e algumas instruções de controle de fluxo mais avançadas...</p>
    
<h3>Considerações Finais</h3>
    <p>O simulador MiniMIPS desenvolvido demonstrou ser uma ferramenta valiosa para experimentação e aprendizado de arquitetura de computadores e programação de sistemas...</p>

<h3>Função <code>tipo</code></h3>
    <p>A função <code>tipo</code> recebe o código de operação (opcode) em formato de string e retorna o tipo de instrução MiniMIPS ('R', 'I' ou 'J') com base no opcode.</p>

<h3>Função <code>lerEArmazenarArquivo</code></h3>
    <p>Esta função lê um arquivo contendo instruções MiniMIPS e armazena essas instruções na memória de instruções do simulador. Cada linha do arquivo é processada e decodificada para extrair o opcode e outros campos relevantes da instrução, que são então armazenados na estrutura de memória de instruções.</p>

<h3>Função <code>result_ula</code></h3>
    <p>Esta função calcula o resultado de uma operação aritmética ou lógica com base no opcode e, opcionalmente, no campo "funct" da instrução MiniMIPS. Os resultados das operações são retornados para serem utilizados pelo simulador.</p>

<h3>Operações do Menu</h3>
    <p>O usuário pode escolher entre várias operações no menu, como carregar instruções, imprimir memória de instruções, imprimir registradores, imprimir todo o simulador, salvar estado atual, executar programa e executar uma única instrução. Cada operação é implementada em um caso de switch.</p>

<h3>Execução de Instruções</h3>
    <p>Na opção "Executar uma instrução", o programa consulta a instrução no contador de programa (PC) atual e executa a operação correspondente com base no opcode da instrução. As operações são implementadas de acordo com o conjunto de instruções MiniMIPS, como operações aritméticas, de transferência de dados e de controle de fluxo.</p>

<h3>Visualização de Memória e Registradores</h3>
    <p>As memórias de instruções e de dados são impressas na tela, mostrando as instruções MiniMIPS e os valores armazenados nas posições de memória. Os valores dos registradores MiniMIPS são exibidos na tela, permitindo ao usuário visualizar o estado atual dos registradores.</p>

<h2>Conclusão</h2>
    <p>O simulador MiniMIPS desenvolvido em linguagem C oferece uma ferramenta valiosa para entender e experimentar com o conjunto de instruções MiniMIPS. Ele permite aos usuários carregar, executar e visualizar instruções MiniMIPS de forma interativa, facilitando a aprendizagem e a experimentação com arquiteturas de computadores. Este projeto demonstra a aplicação prática de conceitos teóricos em um contexto de programação de sistemas e pode ser expandido e aprimorado para incluir mais funcionalidades e suporte a diferentes tipos de instruções e modos de endereçamento.</p>

</body>
</html>
