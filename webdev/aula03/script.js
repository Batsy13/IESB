function addItem() {
  let name = document.getElementById("text").value;
  let number = document.getElementById("number").value;

  if (name == "" || number == "") {
    alert("All inputs are required");
    return;
  }

  const list = document.getElementById("list");
  const listItem = document.createElement("li");

  listItem.innerHTML = `<h2>${name}</h2> <p>${number}</p>`;

  list.appendChild(listItem);
  document.getElementById("text").value = "";
  document.getElementById("number").value = "";
}
