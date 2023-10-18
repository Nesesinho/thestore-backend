const fs = require('fs');

class Data {
    constructor() {
        this.purchases = [];
    }

    add(data){
        this.purchases.push(data);
    }

    convertToQuick(data) {
        console.log(data);
        let convertedData = `${data.name}|${data.age}|${data.purchased[0]}|${data.purchased[1]}|${data.purchased[2]}|`

        Object.entries(data.purchased[3]).forEach(e => {
            if(Object.keys(e[1]).length === 0) return
            Object.entries(e[1]).forEach(e => {
                convertedData += `${e[1].name}-${e[1].quantity}-${e[1].price}|`
            })
        })

        convertedData += "--end"

        return convertedData;
    }

    sendToQuick() {
        this.purchases.forEach(e => {
            fs.appendFile("./quick/quick/dados.txt", this.convertToQuick(e) + '\n', (err) => {
                if (err) {
                  console.error('Ocorreu um erro ao adicionar a informação ao arquivo:', err);
                } else {
                  console.log(`A informação foi adicionada ao arquivo dados.txt com sucesso.`);
                }
              });
        })
        this.purchases = []
    }
}

const data = new Data();
module.exports = { data };