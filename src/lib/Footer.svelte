<script lang="ts">
    import { t } from "svelte-intl-precompile";
	import Logo from "./icons/Logo.svelte";
	import NavLink from "./NavLink.svelte";
</script>

<style lang="scss">
    @import "$styles/footer.scss";
</style>

<footer class="limited-width-container">
    <div class="limited-width-content footer-content">
        <div class="logo">
            <Logo size={50}/>
        </div>

        <div class="links">
            <NavLink props={{label: "page.privacy.title", route: "/privacy"}}/>
            <NavLink props={{label: "page.license.title", route: "/license"}}/>
            <NavLink props={{label: "page.about.title", route: "/about"}}/>
        </div>

        <div class="copyright">
            &copy; Thomas Emil Jensen
        </div>

        <div class="open-source">
            {$t("footer.open-source")}
        </div>
    </div>
</footer>