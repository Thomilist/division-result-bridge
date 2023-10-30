<script lang="ts">
	import ThemeSwitch from './ThemeSwitch.svelte';
	import LanguageSelect from './LanguageSelect.svelte';
	import OptionsIcon from './icons/OptionsIcon.svelte';
	import NavDropdown from './NavDropdown.svelte';
	import NavLink from './NavLink.svelte';
	import NavHomeLink from './NavHomeLink.svelte';
	import Logo from './icons/Logo.svelte';
    
    const home: NavHomeProps =
    {
        label: "project.name",
        route: "/",
        icon: {component: Logo, size: 16}
    };

    const items: NavItem[] =
    [
        {component: NavLink, props: {label: "page.docs.title", route: "/docs"}}
    ];

    const options: NavDropdownProps = {label: "options.name", align: "right", expand: "click", icon: OptionsIcon, items:
    [
        {component: LanguageSelect, props: {label: "options.language.name"}},
        {component: ThemeSwitch, props: {label: "options.theme.name"}}
    ]};
</script>

<style lang="scss">
    @import "$styles/nav-bar.scss";
</style>

<nav class="nav-bar limited-width-container">
    <div class="nav-menu limited-width-content">
        <NavHomeLink props={home}/>
        
        <div class="nav-items">
            <ul>
                {#each items as item}
                    <li class="nav-hoverable">
                        <svelte:component this={item.component} props={item.props}/>
                    </li>
                {/each}
            </ul>
        </div>
    
        <NavDropdown props={options}/>
    </div>
</nav>