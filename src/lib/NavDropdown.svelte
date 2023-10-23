<script lang="ts">
    import { t } from "svelte-intl-precompile";
    import { clickOutside } from "svelte-use-click-outside";

    export let label: string;
    export let icon: any;
    export let items: any;

    let open: boolean = false;
    $: open_class = open ? "is-open" : "";

    function toggleDropdown()
    {
        open = !open;
        return;
    }

    function onClickOutside()
    {
        open = false;
        return;
    }
</script>

<style lang="scss">
    @import "$styles/nav-dropdown.scss";
</style>

<div use:clickOutside={onClickOutside} class="nav-dropdown">
    <button class="nav-hoverable" on:click={toggleDropdown}>
        {#if icon}
            <svelte:component this={icon}/>
        {/if}

        {$t(`${label}`)}
    </button>

    <ul class="nav-dropdown-list {open_class}">
        {#each items as item}
            <li class="nav-hoverable">
                <svelte:component this={item.component} label={item.label}/>
            </li>
        {/each}
    </ul>
</div>