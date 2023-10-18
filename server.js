const express = require('express');
const cors = require('cors');
const { data } = require('./data/Controller.js');

const app = express();
const port = 3000;

app.use(cors());

app.use((req, res, next) => {
      res.header('Access-Control-Allow-Origin', '*'); // Permitir solicitações de qualquer origem
      res.header('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE');
      res.header('Access-Control-Allow-Headers', 'Content-Type');
      next();
  });

app.use(express.json());

app.post('/send', (req, res) => {
  const dadosRecebidos = req.body;
  data.add(dadosRecebidos);
  data.sendToQuick();
  res.send('Recebido com sucesso');
});

app.get('/dados', (req, res) => {
  res.json(data.purchases);
});

app.listen(port, () => {
  console.log(`Servidor Express em execução na porta ${port}`);
});