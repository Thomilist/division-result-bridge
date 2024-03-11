<script lang="ts">
	import NavDropdown from './NavDropdown.svelte';
	import NavHomeLink from './NavHomeLink.svelte';
	import type { NavBarProps } from './types';
    
    export let props: NavBarProps;
</script>



<style lang="scss">
    @import "$styles/nav-bar.scss";
</style>



<nav class="nav-bar limited-width-container">
    <div class="nav-menu limited-width-content">
        <NavHomeLink props={props.home}/>
        
        <div class="nav-items">
            <ul>
                {#each props.items as item}
                    <li class="nav-hoverable">
                        <svelte:component
                            this={item.component}
                            props={item.props}
                        />
                    </li>
                {/each}
            </ul>
        </div>
    
        <NavDropdown props={props.options}/>
    </div>
</nav>
