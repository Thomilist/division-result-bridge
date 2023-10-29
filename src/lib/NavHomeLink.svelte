<script lang="ts">
	import { base } from "$app/paths";
    import { t } from "svelte-intl-precompile";
	export let props: NavHomeProps;
</script>

<style lang="scss">
    @import "$styles/nav-home-link.scss";
</style>

<a href={base}{props.route} class="nav-hoverable">
    <div class="home-link">
        {#if props.icon}
            <div class="icon">
                <svelte:component this={props.icon.component} size={props.icon.size}/>
            </div>
        {/if}
        
        <div class="label">
            {$t(props.label)}
        </div>
    </div>
</a>