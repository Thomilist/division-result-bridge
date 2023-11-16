<script lang="ts">
    import { t } from "svelte-intl-precompile";
    import { clickOutside } from "svelte-use-click-outside";
	import type { NavDropdownProps } from "./types";

    export let props: NavDropdownProps;

    let open: boolean = false;
    $: open_class = open ? "is-open" : "";

    const has_icon: boolean = props.icon !== undefined;
    const has_icon_class = has_icon ? "has-icon" : "";

    function toggleDropdown()
    {
        if (props.expand !== "click")
        {
            return;
        }
        
        open = !open;
        return;
    }

    function onClickOutside()
    {
        if (props.expand !== "click")
        {
            return;
        }
        
        open = false;
        return;
    }
</script>

<style lang="scss">
    @import "$styles/nav-dropdown.scss";
</style>

<div use:clickOutside={onClickOutside} class="nav-dropdown expand-on-{props.expand}">
    <button class="nav-hoverable {has_icon_class}" on:click={toggleDropdown}>
        {#if has_icon}
            <svelte:component this={props.icon} role="presentation"/>
        {/if}

        {$t(`${props.label}`)}
    </button>

    <ul class="nav-dropdown-list {open_class} align-{props.align}">
        {#each props.items as item}
            <li class="nav-hoverable">
                <svelte:component this={item.component} props={item.props}/>
            </li>
        {/each}
    </ul>
</div>