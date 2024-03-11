import DOMPurify from "dompurify";
import { Marked } from "marked";
import hljs from "highlight.js/lib/core";
import plaintext from "highlight.js/lib/languages/plaintext";
import json from "highlight.js/lib/languages/json";
import cpp from "highlight.js/lib/languages/cpp";
import javascript from "highlight.js/lib/languages/javascript";
import typescript from "highlight.js/lib/languages/typescript";
import { markedHighlight } from "marked-highlight";

hljs.registerLanguage("plaintext", plaintext);
hljs.registerLanguage("json", json);
hljs.registerLanguage("cpp", cpp);
hljs.registerLanguage("javascript", javascript);
hljs.registerLanguage("typescript", typescript);

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
