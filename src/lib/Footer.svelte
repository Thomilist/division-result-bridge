<script lang="ts">
    import { t } from "svelte-intl-precompile";
	import Logo from "./icons/Logo.svelte";
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
            <a href="/privacy">
                {$t("page.privacy.title")}
            </a>
            <a href="/about">
                {$t("page.about.title")}
            </a>
        </div>

        <div class="copyright">
            &copy; Thomas Emil Jensen
        </div>

        <div class="open-source">
            {$t("footer.open-source")}
        </div>
    </div>
</footer>