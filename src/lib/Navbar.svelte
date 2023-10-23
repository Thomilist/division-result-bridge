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
    <div class="nav-links">
        <ul>
            {#each links as link}
                <li>
                    <a href="{base}{link.route}">{$t(link.name)}</a>
                </li>
            {/each}
        </ul>
    </div>

    <div class="nav-options-dropdown">
        <input type="checkbox" id="nav-options-dropbown-input"/>
        <label for="nav-options-dropbown-input">Options</label>

        <ul class="nav-options-list">
            <li>
                <div class="nav-dropdown-item">
                    <ThemeSwitch label="Theme:"/>
                </div>
            </li>
    
            <li>
                <div class="nav-dropdown-item">
                    <LanguageSelect label="Language:"/>
                </div>
            </li>
        </ul>
    </div>
</nav>