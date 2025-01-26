const quotes = [
	{
		quote: "a",
		author: "A",
	},
	{
		quote: "b",
		author: "B",
	},
	{
		quote: "c",
		author: "C",
	},
	{
		quote: "d",
		author: "D",
	},
	{
		quote: "e",
		author: "E",
	},
]

const quote = document.querySelector("#quote span:first-child");
const author = document.querySelector("#quote span:last-child");

const todaysQuote = quotes[Math.floor(Math.random() * quotes.length)];

quote.innerText = todaysQuote.quote;
author.innerText = todaysQuote.author;
