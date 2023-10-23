<script lang="ts">
    import { t } from 'svelte-intl-precompile';
	import ThemeSwitch from './ThemeSwitch.svelte';
	import LanguageSelect from './LanguageSelect.svelte';
	import { base } from '$app/paths';
	import OptionsIcon from './icons/OptionsIcon.svelte';
	import NavDropdown from './NavDropdown.svelte';
    
    const links =
    [
        {name: "page.home.title", route: "/"},
        {name: "page.about.title", route: "/about"},
    ];

    const options =
    [
        {component: LanguageSelect, label: "options.language.name"},
        {component: ThemeSwitch, label: "options.theme.name"}
    ];
</script>

<style lang="scss">
    @import "$styles/navbar.scss";
</style>

<nav class="navbar">
    <div class="nav-links">
        <ul>
            {#each links as link}
                <li>
                    <a href="{base}{link.route}" class="nav-hoverable">{$t(link.name)}</a>
                </li>
            {/each}
        </ul>
    </div>

    <NavDropdown label="options.name" icon={OptionsIcon} items={options}/>
</nav>