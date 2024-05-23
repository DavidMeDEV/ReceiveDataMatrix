var express = require('express')
const WebSocket = require('ws')
var fs = require('fs')
var path = require('path');
const bodyParser = require('body-parser');
const axios = require('axios');

let app = express()
var text= 'SEM DADOS NA FILA'
var textConcat= ''
app.use(bodyParser.json());

const porta = 3000

const websocket = new WebSocket.Server({ port: 80 });
var user = [];

websocket.on('connection', function (ws) {
    ws.on('error', console.error)
    console.log(`clientes conectados ${ws.url}`)
    user.push(ws)
    ws.on('message', function message(event) {
        if (event.toString('utf8') != undefined) {
            if (event.toString('utf8') != "Connected") {
                text = event.toString('utf8')
                textConcat+=text
                ws.send('11')
                console.log(text)
            }
        }
        user.map(user => {
            user.send(event)
        })
    });
});

app.use(express.static(path.join(__dirname, "/src/Server")));
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/src/Server/index.html')
})

app.get('/mensagem', (req, res) => {
        res.send({content:textConcat})
    return textConcat='' 

})

app.listen(porta, () => {
    console.clear()
    console.log(`server rodando em ${porta}`)
})