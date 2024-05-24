from typing import Callable, ClassVar, overload

maximization: problem_type
minimization: problem_type

class ga:
    def __init__(self, arg0: int, arg1: int, arg2: list[int], arg3: int, arg4: problem_type) -> None: ...
    def evaluate_offsprings(self, arg0: Callable, *args) -> None: ...
    def evaluate_population(self, arg0: Callable, *args) -> None: ...
    def generate_population(self) -> None: ...
    def get_best_individual(self) -> individual: ...
    def get_genome_length(self) -> int: ...
    def get_population(self) -> list[individual]: ...
    def get_population_size(self) -> int: ...
    def one_point_crossover(self) -> None: ...
    def one_point_crossover_v2(self) -> None: ...
    def random_crossover(self) -> None: ...
    def random_mutation(self, arg0: float) -> None: ...
    def replace(self) -> None: ...
    def rotate_mutation(self, arg0: float) -> None: ...
    def roulette(self) -> None: ...
    def shuffle_generate_population(self) -> None: ...
    def swap_mutation(self, arg0: float) -> None: ...
    def tournament(self) -> None: ...

class individual:
    @overload
    def __init__(self, arg0: list[int]) -> None: ...
    @overload
    def __init__(self, arg0: individual) -> None: ...
    def get_fitness(self) -> int: ...
    def get_genome(self) -> list[int]: ...
    def set_fitness(self, arg0: int) -> None: ...
    def set_genome(self, arg0: list[int]) -> None: ...
    def __eq__(self, arg0: individual) -> bool: ...
    def __ge__(self, arg0: individual) -> bool: ...
    def __gt__(self, arg0: individual) -> bool: ...
    def __le__(self, arg0: individual) -> bool: ...
    def __lt__(self, arg0: individual) -> bool: ...

class problem_type:
    __members__: ClassVar[dict] = ...  # read-only
    __entries: ClassVar[dict] = ...
    maximization: ClassVar[problem_type] = ...
    minimization: ClassVar[problem_type] = ...
    def __init__(self, value: int) -> None: ...
    def __eq__(self, other: object) -> bool: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: object) -> bool: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...
