<script lang="ts">
	import Image from "../Image.svelte";
	import type { DocImageProps } from "../types";
	import { t } from "svelte-intl-precompile";
	import { tpage } from "./docs";

    export let props: DocImageProps;

    const alt_values = Object.assign({}, props.values?.common, props.values?.alt);
    const caption_values = Object.assign({}, props.values?.common, props.values?.caption);
</script>

<Image props={
{
    src: props.src,
    alt: $t(tpage(props.docpage, [...props.specifiers, "alt"]), {values: alt_values}),
    caption: $t(tpage(props.docpage, [...props.specifiers, "caption"]), {values: caption_values})
}}/>