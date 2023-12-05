<script lang="ts">
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
            {props.caption}
        </figcaption>
    {/if}
</figure>