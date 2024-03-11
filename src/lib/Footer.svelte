<script lang="ts">
    import { t } from "svelte-intl-precompile";
	import Logo from "./icons/Logo.svelte";
	import NavLink from "./NavLink.svelte";
	import { resources } from "./resources";
</script>



<style lang="scss">
    @import "$styles/footer.scss";
</style>



<footer class="limited-width-container">
    <div class="limited-width-content footer-content narrow-content">
        <div class="logo">
            <Logo size={50}/>
        </div>

        <div class="links">
            <NavLink props=
            {{
                label: resources.internal.privacy.label,
                route: resources.internal.privacy.route
            }}/>
            <NavLink props=
            {{
                label: resources.internal.license.label,
                route: resources.internal.license.route
            }}/>
            <NavLink props=
            {{
                label: resources.internal.about.label,
                route: resources.internal.about.route
            }}/>
            <NavLink props=
            {{
                label: resources.internal.source.label,
                route: resources.external.thomilist.project.division_result_bridge.route.repo,
                target: "_blank"
            }}/>
        </div>

        <div class="copyright">
            &copy; {$t("project.author")}
        </div>

        <div class="open-source">
            {$t("footer.open-source")}
        </div>
    </div>
</footer>
