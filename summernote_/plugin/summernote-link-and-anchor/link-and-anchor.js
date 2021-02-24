//自定义插件,链接和锚点
(function (factory) {
    /* Global define */
    if (typeof define === 'function' && define.amd) {
        // AMD. Register as an anonymous module.
        define(['jquery'], factory);
    } else if (typeof module === 'object' && module.exports) {
        // Node/CommonJS
        module.exports = factory(require('jquery'));
    } else {
        // Browser globals
        factory(window.jQuery);
    }
}(function ($) {
    $.extend(true, $.summernote.lang, {
        'en-US': {
            tooltip: "line",
        },
        'zh-CN': {
            brush: {
                tooltip: "链接和锚点(CTRL+K)",
            }
        }
    });

    $.extend($.summernote.plugins, {
        'linknanchor': function (context) {
            var self = this,
                ui = $.summernote.ui,
                options = context.options,
                func = options.func,
                $note = context.layoutInfo.note,
                $editor = context.layoutInfo.editor,
                $editable = context.layoutInfo.editable,
                $toolbar = context.layoutInfo.toolbar,
                $container = options.dialogsInBody ? $(document.body) : $editor,
                lang = options.langInfo;

            var link = ui.button({
                contents: "<li class='fa fa-link'></li>",
                tooltip: "插入链接",
                click: context.createInvokeHandler('linkDialog.show'),
            });
            var anchor = ui.button({
                contents: "<li class='fa fa-anchor'></li>",
                tooltip: "创建书签",
                click: context.createInvokeHandler("add-anchors.show"),
            });
            var unlink = ui.button({
                contents: "<li class='fa fa-unlink'></li>",
                tooltip: "删除链接/书签",
                click: context.createInvokeHandler('editor.unlink'),
            });
            var linkTo = ui.button({
                contents: "<li class='fa fa-arrows'></li>",
                tooltip: "链接到书签",
                click: context.createInvokeHandler("list-of-links.show"),
            });

            context.memo('button.link', func.invoke(link, 'render'));
            context.memo('button.anchor', func.invoke(anchor, 'render'));
            context.memo('button.unlink', func.invoke(unlink, 'render'));
            context.memo("button.linkTo", func.invoke(linkTo, 'render'));

            context.memo("button.linknanchor", () => {
                return ui.buttonGroup([
                    ui.button({
                        className: 'dropdown-toggle',
                        contents: ui.dropdownButtonContents('<i class="note-icon-link"></i>', options),
                        tooltip: lang.brush.tooltip,
                        data: {
                            toggle: 'dropdown',
                        },
                    }),
                    ui.dropdown([
                        ui.buttonGroup({
                            className: 'note-link-anchor',
                            children: [link, anchor, unlink, linkTo],
                        }),
                    ])]
                ).render();
            });
        }
    });
}));