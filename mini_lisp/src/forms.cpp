//
// Created by 王愉博 on 24-5-23.
//
#include"forms.h"
#include"error.h"

const std::unordered_map<std::string, SpecialFormType *> SPECIAL_FORMS{
        {"define", &defineForm},
//        {"if", &ifForm},
//        {"and",&andForm},
//        {"or",&orForm},
//        {"lambda", &lambdaForm},
        {"quote", &quoteForm},
//    {"set!", &setForm},
};

ValuePtr defineForm(const std::vector<ValuePtr> &args, EvalEnv &env) {
    if (args.size() != 2) {
        throw LispError("define form must have 2 arguments");
    }
    if (args[0]->isSymbol()) {
        env.defineBinding(*args[0]->asSymbol(), env.eval(args[1]));
        return std::make_shared<NilValue>();
    } else {
        throw LispError("unimplemented define form");
    }
}

ValuePtr quoteForm(const std::vector<ValuePtr> &params, EvalEnv &env) {
    if(params.size()!=1){//quote特殊形式只能有一个参数
        throw LispError("quote form must have exactly one argument.");
    }
    return params[0]->toQuote();
}
