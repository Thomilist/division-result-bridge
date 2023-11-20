<script lang="ts">
	import { t } from "svelte-intl-precompile";
	import type { ImageProps } from "./types";

    export let props: ImageProps;
</script>

<style lang="scss">
    @import "$styles/image.scss";
</style>

<figure>
    <img src={props.src} alt={props.alt}/>

    {#if props.caption}
        <figcaption>
            {$t(props.caption)}
        </figcaption>
    {/if}
</figure>