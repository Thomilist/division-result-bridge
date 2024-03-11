<script lang="ts">
	import { t } from "svelte-intl-precompile";

    export let style: "tip" | "warning";
</script>



<style lang="scss">
    @import "$styles/doc-highlighted-textbox.scss";
</style>



<div class="doc-highlighted-textbox">
    <b>
        {#if style === "tip"}
            ℹ️
        {:else if style === "warning"}
            ⚠️
        {/if}

        {$t(`ui.${style}`)}
    </b>
    
    <slot/>
</div>
