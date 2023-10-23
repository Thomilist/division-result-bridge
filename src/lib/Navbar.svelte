<script lang="ts">
    import { t } from 'svelte-intl-precompile';
	import ThemeSwitch from './ThemeSwitch.svelte';
	import LanguageSelect from './LanguageSelect.svelte';
	import { base } from '$app/paths';
	import OptionsIcon from './icons/OptionsIcon.svelte';
    
    const links =
    [
        {name: "page.home.title", route: "/"},
        {name: "page.about.title", route: "/about"},
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

    <div class="nav-options-dropdown">
        <input type="checkbox" id="nav-options-dropbown-input"/>
        <label for="nav-options-dropbown-input" class="nav-hoverable"><OptionsIcon/>{$t("options.name")}</label>

        <ul class="nav-options-list">
            <li>
                <div class="nav-dropdown-item nav-hoverable">
                    <LanguageSelect label="options.language.name"/>
                </div>
            </li>

            <li>
                <div class="nav-dropdown-item nav-hoverable">
                    <ThemeSwitch label="options.theme.name"/>
                </div>
            </li>
        </ul>
    </div>
</nav>