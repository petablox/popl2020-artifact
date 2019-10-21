from bench import *
import os

KD_bench = [path, scc, abduce, ancestor, animals, buildwall, samegen, inflamation]

PA_simpl = [rvcheck, polysite, downcast, escape, andersen, modref]
PA_complex = [one_call_site, one_obj, one_type, one_obj_type, two_call_site]
PA_bench = PA_simpl + PA_complex

SQL_bench = [sql_1, sql_2, sql_3, sql_4, sql_5, sql_6, sql_7, sql_8, sql_9, sql_10, sql_11, sql_12, sql_13, sql_14, sql_15 ]


def get_template(bench):
    if bench in PA_complex:
        if bench == one_call_site:
            return "type_pointer.t"
        elif bench == two_call_site:
            return "2-call-site-input.t"
        elif bench == one_obj_type:
            return "1-obj-type-input.t"
        else:
            return "1-call-site.t"
    elif bench == rvcheck:
            return "openssl.t"
    elif bench in [andersen, modref]:
        return "default.t"
    else:
        return None


def get_data(bench):
    data_dir = None
    fname = "%s.d" % bench

    if bench in KD_bench:
        data_dir = "benchmarks/"
    if bench in PA_simpl:
        data_dir = "benchmarks/"
    if bench in PA_complex:
        data_dir = "benchmarks/pa_complex/"
    if bench in SQL_bench:
        data_dir = "sql_bench/"

    fpath = os.path.join(data_dir, fname)
    return fpath






bidirect = "bidirect"
staged = "staged"
maxK = "rulePerIDB"
maxM = "maxRules"

graph = "-G"
filter2 = "--f2"
filter1 = "--f1"
chain1 = "--projection"
chain2 = "--chain2"
chain3 = "--chain3"
bindings = lambda x: "--bindings={}".format(x)
distinctR = lambda x: "-d {}".format(x)

headbinding = "--headBinding"

alps_config = {
    path : {
        bidirect : {
            maxK : 2,
            maxM : 2,
        },
        staged : (0, [chain1, chain2]),
    },

    scc : {
        bidirect : {
            maxK : 2,
            maxM : 3,
        },
        staged : (2, [chain1, chain2, bindings(1)]),
    },

    abduce : {
        bidirect : {
            maxK : 2,
            maxM : 3,
        },
        staged : (0, [chain1, chain2]),
    },

    ancestor : {
        bidirect : {
            maxK : 2,
            maxM : 4,
        },
        staged : (0, [chain1, chain2]),
    },

    animals : {
        bidirect : {
            maxK : 1,
            maxM : 4,
        },
        staged : (3, [chain1, filter1]),
    },

    buildwall : {
        bidirect : {
            maxK : 2,
            maxM : 3,
        },
        staged : (2, [filter1, chain2]),
    },

    samegen : {
        bidirect : {
            maxK : 2,
            maxM : 2,
        },
        staged : (2, [chain2, chain3]),
    },

    inflamation: {
        bidirect : {
            maxK : 2,
        },
        staged : (4, [chain2]),
    },

    rvcheck : {
        bidirect : {
            maxK : 1,
        },
    },

    polysite : {
        bidirect : {
            maxK : 1,
            maxM : 3,
        },
        staged : (3, [chain1, bindings(1), chain3]),
    },

    downcast : {
        bidirect : {
            maxK : 1,
        },
        staged : (3, [chain1, chain2, bindings(2)]),
    },

    andersen : {
        bidirect : {
            maxK : 4,
        },
    },

    escape : {
        bidirect : {
            maxK : 2,
            maxM : 6,
        },
        staged : (1, [chain2, chain1]),
    },

    modref : {
        bidirect : {
            maxK : 2,
            maxM : 10,
        },
    },


    one_call_site : {
        bidirect : {
            maxK : 3,
            maxM : 4,
        },
        staged : (3, [chain2, chain1, bindings(1)]),
    },

    one_obj : {
        bidirect : {
            maxK : 3,
            maxM : 4,
        },
        staged : (1, [chain3, chain1, graph]),
    },

    one_type : {
        bidirect : {
            maxK : 3,
            maxM : 4,
        },
        staged : (2, [chain2, chain1]),
    },

    two_call_site : {
        bidirect : {
            maxK : 3,
            maxM : 4,
        },
        staged : (3, [chain2]),
    },

    one_obj_type : {
        bidirect : {
            maxK : 3,
            maxM : 4,
        },
        staged : (2, [chain2]),
    },

    sql_1 : {
        bidirect : {
            maxK : 1,
            maxM : 1,
        },
        staged : (4, [chain3]),
    },

    sql_9 : {
        bidirect : {
            maxK : 1,
            maxM : 2,
        },
        staged : (4, [chain3]),
    },

    sql_2 : {
        bidirect : {
            maxK : 1,
            maxM : 1,
        },
        staged : (5, [chain2]),
    },

    sql_14 : {
        bidirect : {
            maxK : 1,
            maxM : 2,
        },
        staged : (5, [chain2,chain3]),
    },

    sql_3 : {
        bidirect : {
            maxK : 1,
            maxM : 1,
        },
        staged : (2, [chain1]),
    },

    sql_10 : {
        bidirect : {
            maxK : 1,
            maxM : 2,
        },
        staged : (3, [chain3, chain1, bindings(1)]),
    },

    sql_4 : {
        bidirect : {
            maxK : 2,
            maxM : 2,
        },
        staged : (3, [chain1, filter1]),
    },

    sql_13 : {
        bidirect : {
            maxK : 1,
            maxM : 1,
        },
        staged : (2, [chain2]),
    },

    sql_6 : {
        bidirect : {
            maxK : 2,
            maxM : 2,
        },
        staged : (2, [chain1,headbinding]),
    },

    sql_7 : {
        bidirect : {
            maxK : 1,
            maxM : 1,
        },
        staged : (1, [chain1]),
    },

    sql_11 : {
        bidirect : {
            maxK : 1,
            maxM : 4,
        },
        staged : (4, [chain2, filter1]),
    },

    sql_15 : {
        bidirect : {
            maxK : 1,
            maxM : 2,
        },
        staged : (3, [chain2, chain3, bindings(2)]),
    },

    sql_5 : {
        bidirect : {
            maxK : 1,
            maxM : 1,
        },
        staged : (1, [chain2]),
    },

    sql_12 : {
        bidirect : {
            maxK : 2,
            maxM : 3,
        },
        staged : (2, [chain1, filter1, chain3]),
    },

    sql_8 : {
        bidirect : {
            maxK : 2,
            maxM : 3,
        },
        staged : (2, [chain1, filter1, chain2]),
    },
}

