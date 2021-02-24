//自定义插件，分割线
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
            hr: {
                tooltip: "分割线(CTRL+ENTER)",
            }
        }
    });

    $.extend($.summernote.plugins, {
        'spliteline': function (context) {
            var self = this,
                ui = $.summernote.ui,
                options = context.options,
                $note = context.layoutInfo.note,
                $editor = context.layoutInfo.editor,
                $editable = context.layoutInfo.editable,
                $toolbar = context.layoutInfo.toolbar,
                $container = options.dialogsInBody ? $(document.body) : $editor,
                lang = options.langInfo;

            context.memo("button.spliteline", () => {
                return ui.buttonGroup([
                    ui.button({
                        className: 'note-btn-splite-line',
                        contents: ui.dropdownButtonContents('<i class="fa fa-minus"></i>', options),
                        tooltip: lang.hr.tooltip,
                        data: {
                            toggle: 'dropdown',
                        },
                    }),
                    ui.dropdown({
                        className: 'note-btn-splite-line',
                        //checkClassName: options.icons.menuCheck,
                        items: [
                            "<hr style='border-top: 1px dotted #8c8b8b;'>",
                            "<hr style='height:1px;border:none;border-top:1px dashed #0066CC;'>",
                            "<hr style='height:1px;border:none;border-top:1px solid #555555;'>",
                            "<hr style='height:3px;border:none;border-top:3px double red;'>",
                            "<hr style='height:5px;border:none;border-top:5px ridge green;'>",
                            "<hr style='height:10px;border:none;border-top:10px groove skyblue;'>",
                        ],
                        title: lang.font.size,
                        click: context.createInvokeHandlerAndUpdateState('editor.insertUserDefRule'),
                    })]).render();
            });
        }
    });
}));