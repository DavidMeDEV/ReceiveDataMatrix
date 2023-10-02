let printar = document.getElementById('h1')
let dataToSave = "";

function claimFetch() {

  fetch('http://localhost:3000/mensagem')
    .then(response => {

      if (!response.ok) {
        throw new Error('Não foi possível completar a solicitação.');
      }

      return response.json();
    })
    .then(data => {
      console.log(data.content);
      printar.innerText = data.content
      dataToSave = data.content
    })
    .catch(error => {
      console.error('Ocorreu um erro:', error);
    });
}

function saveData() {

  var conteudo = dataToSave;

  var blob = new Blob([conteudo], { type: "text/plain" });

  var a = document.createElement("a");
  a.href = URL.createObjectURL(blob);
  a.download = "Dados_Matriz";
  document.body.appendChild(a);
  a.click();
  document.body.removeChild(a);
}


console.log('funciona')