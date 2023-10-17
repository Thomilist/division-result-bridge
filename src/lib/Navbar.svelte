<script lang="ts">
    import { t } from 'svelte-intl-precompile';
	import ThemeSwitch from './ThemeSwitch.svelte';
	import LanguageSelect from './LanguageSelect.svelte';
	import { base } from '$app/paths';
    
    const links =
    [
        {name: "page.home.title", route: "/"},
        {name: "page.about.title", route: "/about"},
    ];
</script>

<style lang="scss">
    @import "$styles/navbar.scss";
</style>

<nav>
    <ul class="nav-links">
        {#each links as link}
            <li>
                <a href="{base}{link.route}">{$t(link.name)}</a>
            </li>
        {/each}
    </ul>

    <ul class="nav-settings">
        <li>
            <div>
                <ThemeSwitch/>
            </div>
        </li>

        <li>
            <div>
                <LanguageSelect/>
            </div>
        </li>
    </ul>
</nav>