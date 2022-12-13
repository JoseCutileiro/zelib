import React from 'react';
import ReactMarkdown from 'react-markdown';

const MarkdownExample = () => {
  const markdown = `
# This is a Markdown heading

And here's some Markdown-formatted text. You can include **bold**, *italic*, or ~~strikethrough~~ text, as well as [links](https://www.example.com) and images:

![An example image](https://www.example.com/image.png)

And you can even include code blocks:

\`\`\`
const foo = 'bar';
console.log(foo);
\`\`\`
  `;

  return <ReactMarkdown source={markdown} />;
};
