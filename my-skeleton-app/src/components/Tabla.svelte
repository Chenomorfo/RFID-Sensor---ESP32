<script lang="ts">
    import {
        Table,
        tableMapperValues,
        type TableSource,
    } from "@skeletonlabs/skeleton";

    export let sourceData: {
        nombre: string;
        nivel: number;
        fecha: string;
    }[] = [];
</script>

<!-- component -->
<div class="flex items-center justify-center">
    <div class="overflow-x-auto">
        <table class="min-w-full bg-white shadow-md rounded-xl">
            <thead>
                <tr class="bg-blue-gray-100 text-gray-700">
                    <th class="py-3 px-4 text-left">Nombre</th>
                    <th class="py-3 px-4 text-left">Nivel</th>
                    <th class="py-3 px-4 text-left">Fecha</th>
                </tr>
            </thead>
            <tbody class="text-blue-gray-900">
                {#each sourceData as row}
                    <tr class="border-b border-blue-gray-200 text-black">
                        <td class="py-3 px-4">{row.nombre}</td>
                        <td class="py-3 px-4">{row.nivel}</td>
                        <td class="py-3 px-4">{row.fecha}</td>
                    </tr>
                {/each}
            </tbody>
        </table>
    </div>
</div>
