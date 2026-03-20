const input = document.querySelector("#numbersInput");
const button = document.querySelector("#sortBtn");
const table = document.querySelector("#resultTable");
const message = document.querySelector("#message");


function sortArray(arr) {
  return arr.sort((a, b) => a - b);
}

function parseArr(text) {
  const tokens = text
    .trim()
    .split(/[\s]+/)
    .filter(Boolean);


  const numbers = tokens.map((n) => Number(n));
  
  const hasInvalid = numbers.some((n) => Number.isNaN(n));

  if (hasInvalid) {
    return null;
  }

  return numbers;
}

function renderTable(sortedNumbers) {
  table.innerHTML = "";

  const cols = 5;

  for (let i = 0; i < sortedNumbers.length; i += cols) {
    row = document.createElement("tr");

    for (let j = 0; j < cols; j++) {
      const cell = document.createElement("td");
      const value = sortedNumbers[i + j];
      cell.textContent = value;
      row.appendChild(cell);
    }

    table.appendChild(row);
  }
}

button.addEventListener("click", () => {
  message.textContent = "";

  const parsedArr = parseArr(input.value);

  if (parsedArr.length === 0) {
    message.textContent = "Enter atleast one number"
  }

  if (parseArr == null)  {
    message.textContent = "Enter only numbers!"
  }
  
  const sortedArray = sortArray(parsedArr);

  
  renderTable(sortedArray);

});

