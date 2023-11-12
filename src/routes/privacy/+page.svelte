<script lang="ts">
	import { resources } from "$lib/resources";
	import { title } from "$lib/stores";
    import { t } from "svelte-intl-precompile";

    $title = `${$t("page.privacy.title")} - ${$t("project.name")}`;
</script>

<div class="narrow-content">
    <h1>
        {$t("page.privacy.title")}
    </h1>
    
    <p>
        {$t("page.privacy.intro")}
    </p>
    
    <p>
        {@html $t("page.privacy.tldr")}
    </p>
    
    <h2>
        {$t("page.privacy.website.title")}
    </h2>
    
    <p>
        {@html $t("page.privacy.website.content", {values: {web_storage_api_link: resources.external.mozilla.projects.mdn.routes.web_storage_api}})}
    </p>
    
    <h2>
        {$t("page.privacy.application.title")}
    </h2>
    
    <p>
        {@html $t("page.privacy.application.settings", {values: {qsettings_link: resources.external.qt.projects.qt6.routes.qsettings}})}
    </p>
    
    <p>
        {@html $t("page.privacy.application.results")}
    </p>
</div>