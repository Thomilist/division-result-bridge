import DOMPurify from "dompurify";
import { Marked } from "marked";
import hljs from "highlight.js/lib/core";
import plaintext from "highlight.js/lib/languages/plaintext";
import { markedHighlight } from "marked-highlight";

hljs.registerLanguage("plaintext", plaintext);

const marked = new Marked(
    markedHighlight({
        highlight(code, lang) {
            const language = hljs.getLanguage(lang) ? lang : "plaintext";
            return hljs.highlight(code, { language }).value;
        }
    })
)

export async function htmlFromMarkdown(markdown: string)
{
    return DOMPurify.sanitize
    (
        await marked.parse
        (
            markdown.replace
            (
                // Remove leading zero-width characters to help markedjs
                /^[\u200B\u200C\u200D\u200E\u200F\uFEFF]/,""
            )
        )
    );
}