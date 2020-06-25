Foram feitos varios teste e corrigidos varios bugs, porém, um ainda permanece.
O bug em questão está no tratamento de espaços, havendo algum o programa acaba por apresentar erro. Exemplo "<html> --funcional--" "<html > --não funcional--"
Isso acontece pois para ler as tags foi usado a função fscanf() que irá ler uma string até encontrar um espaço ou quebra de linha.
A solução que eu tentei implementar foi usar fgets() (que le a string inteira mesmo com espaços) porém, diversas outras complicações apareceram.