<script lang="ts">
	import Image from "./Image.svelte";
	import type { DocImageProps } from "./types";
	import { t } from "svelte-intl-precompile";
	import { tpage } from "./docs/docs";

    export let props: DocImageProps;
</script>

<Image props={
{
    src: props.src,
    alt: $t(tpage(props.docpage, [...props.specifiers, "alt"]), {values: props.values}),
    caption: $t(tpage(props.docpage, [...props.specifiers, "caption"]), {values: props.values})
}}/>