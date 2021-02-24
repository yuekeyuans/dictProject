//自定义插件，格式刷
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
            tooltip: "brush",
        },
        'zh-CN': {
            brush: {
                tooltip: "格式刷",
            }
        }
    });

    $.extend($.summernote.plugins, {
        'brush': function (context) {
            var self = this,
                ui = $.summernote.ui,
                options = context.options,
                $note = context.layoutInfo.note,
                $editor = context.layoutInfo.editor,
                $editable = context.layoutInfo.editable,
                $toolbar = context.layoutInfo.toolbar,
                $container = options.dialogsInBody ? $(document.body) : $editor
            lang = options.langInfo;

            $brushInfo = {};
            $active = false;

            context.memo("button.brush", function () {
                const $cont = $container || $toolbar;
                this.$button = ui.button({
                    className: 'note-btn-brush',
                    contents: '<i class="fa fa-paint-brush"></i>',
                    tooltip: "格式刷",
                    click: function (e) {
                        if ($active) {
                            console.log("brush it!");
                            self.brushIt(e);
                        } else {
                        }
                    },
                    dblclick: function (e) {
                        //转换选中状态
                        $active = $.isEmptyObject($brushInfo);
                        context.invoke('buttons.updateBtnStates', $cont, {
                            '.note-btn-brush': () => $active
                        });
                        if ($active) {
                            const styleInfo = context.invoke('editor.currentStyle');
                            $brushInfo = styleInfo;
                            for (var bi in $brushInfo) {
                                console.log(bi, $brushInfo[bi]);
                            }

                        } else {
                            $brushInfo = {};
                        }
                    }
                });
                return this.$button.render();
            });
            self.brushIt = function (event) {
                const $cont = $container || this.$toolbar;
                const styleInfo = $brushInfo;

                //消除 样式表

                context.invoke("editor.removeFormat");

                if (styleInfo['font-bold'] && styleInfo['font-bold'] != "normal") {
                    context.invoke('editor.bold');
                }
                if (styleInfo['font-italic'] && styleInfo['font-italic'] != "normal") {
                    context.invoke('editor.italic', styleInfo['font-italic']);
                }
                if (styleInfo['font-underline'] && styleInfo['font-underline'] != "normal") {
                    context.invoke('editor.underline');
                }
                if (styleInfo['font-strikethrough'] && styleInfo['font-strikethrough'] != "normal") {
                    context.invoke('editor.strikethrough');
                }
                if (styleInfo['font-subscript'] && styleInfo['font-subscript'] != "normal") {
                    context.invoke('editor.subscript');
                }
                if (styleInfo['font-superscript'] && styleInfo['font-superscript'] != "normal") {
                    context.invoke('editor.superscript');
                }


                if (true) {
                    //context.invoke('editor.fontStyling', 'font-size', styleInfo['font-size'] + "px");
                    //context.invoke('editor.fontStyling', 'font-size', styleInfo['font-size'] + "px");
                    var _selection = document.getSelection()
                    var _range = _selection.getRangeAt(0);
                    var execStyle = function () {
                        var spanString = $('<span/>', {
                            'text': _selection
                        });
                        if (styleInfo['font-size']) {
                            spanString.css('font-size', styleInfo['font-size'] + "px");
                        }
                        if (styleInfo['font-family']) {
                            spanString.css('font-family', styleInfo['font-family']);
                        }
                        if (styleInfo['text-align']) {
                            spanString.css('text-align', styleInfo['text-align']);
                        }
                        if (styleInfo['line-height']) {
                            spanString.css('line-height', styleInfo['line-height']);
                        }
                        if (styleInfo['list-style']) {
                            spanString.css('list-style', styleInfo['list-style']);
                        }
                        if (styleInfo['font-bold']) {
                            spanString.css("font-weight", styleInfo['font-bold']);
                        }
                        if (styleInfo['font-italic']) {
                            spanString.css("font-style", styleInfo['font-italic']);
                        }
                        if (styleInfo['forecolor']) {
                            spanString.css("color", styleInfo['forecolor']);
                        }
                        if (styleInfo['backcolor']) {
                            spanString.css("background-color", styleInfo['backcolor']);
                        }
                        if (styleInfo['font-strikethrough'] || styleInfo['font-underline']) {
                            var s = ""
                            if (styleInfo['font-strikethrough'] != "normal") {
                                s += " line-through";
                            }
                            if (styleInfo['font-strikethrough'] != "normal") {
                                s += " underline";
                            }
                            spanString.css("text-decoration", s);
                        }

                        document.execCommand('insertHTML', false, spanString.prop("outerHTML"));
                    }
                    execStyle();
                }

                //更新样式表
                context.invoke("buttons.updateCurrentStyle");
            }
        }
    });
}));